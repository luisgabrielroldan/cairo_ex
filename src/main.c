#include "cairo_ex.h"
#include "router.h"
#include "transport.h"
#include "erlcmd.h"

#include <err.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


static struct erlcmd handler;
static struct pollfd fdset[1];

static void handle_request(const uint8_t *buffer, size_t length, void *_cookie)
{
    int err = 0;
    cx_result_t result;
    const char *term_data = (const char *)&buffer[2];

    if ((err = router_handle(term_data, length, &result)) == CX_STATUS_OK) {
        transport_send_cmd_response(&result);
        result_free(&result);
    } else {
        errx(EXIT_FAILURE, "Unexpected failure! error=%d", err);
    }
}

int main (int argc, char *argv[])
{
    ei_init();
    erlcmd_init(&handler, handle_request, NULL);

    fdset[0].fd = STDIN_FILENO;
    fdset[0].events = POLLIN;
    fdset[0].revents = 0;

    for (;;) {
        int rc = poll(fdset, 1, -1);

        if (rc < 0)
            err(EXIT_FAILURE, "poll");

        if (fdset[0].revents & (POLLIN | POLLHUP))
            erlcmd_process(&handler);
    }
}
