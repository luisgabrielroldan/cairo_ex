#include "transport.h"
#include "erlcmd.h"

#include <stdarg.h>
#include <string.h>

void transport_send_cmd_response(cx_result_t *result)
{
    uint8_t response[result->index + 3];
    response[2] = TRANSPORT_PACKET_CMD_RESULT;
    memcpy(&response[3], result->buff, result->index);
    erlcmd_send(response, result->index + 3);
}

void transport_send_log_message(char level, const char *fmt, ...)
{
    uint8_t message[256];

    va_list ap;
    va_start(ap, fmt);
    int size = vsnprintf((char *) &message[4], sizeof(message) - 4, fmt, ap);
    va_end(ap);

    if (size > 0) {
        message[2] = TRANSPORT_PACKET_LOG_MESSAGE;
        message[3] = level;
        erlcmd_send(message, size + 4);
    }
}
