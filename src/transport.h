#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "cairo_ex.h"
#include "result.h"

#define TRANSPORT_PACKET_LOG_MESSAGE    0x10
#define TRANSPORT_PACKET_CMD_RESULT     0x20

void transport_send_cmd_response(cx_result_t *result);
void transport_send_log_message(char level, const char *fmt, ...);

#endif
