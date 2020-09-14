#ifndef CAIRO_EX_H
#define CAIRO_EX_H

#include <err.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <ei.h>

void transport_send_log_message(char level, const char *fmt, ...);

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_DEBUG 2

#ifdef DEBUG
#define debug(...) do { transport_send_log_message(2, __VA_ARGS__); } while(0)
#else
#define debug(...)
#endif
#define warn(...) do { transport_send_log_message(1, __VA_ARGS__); } while (0)
#define fatal(...) do { transport_send_log_message(0, __VA_ARGS__); exit(EXIT_FAILURE); } while (0)

inline void debug_term(const char *buf, int *index) {
  int index_save = *index;
  char *str = NULL;
  ei_s_print_term(&str, buf, index);
  debug(str);
  free(str);
  *index = index_save;
}

typedef enum _cx_status_t {
  CX_STATUS_OK = 0,
  CX_STATUS_DECODE_ERROR = INT_MIN,
  CX_STATUS_ENCODE_ERROR,
  CX_STATUS_UNKNOWN_METHOD,
  CX_STATUS_INVALID_REFERENCE,
} cx_status_t;

typedef unsigned long cx_res_handle_t;

#define CX_RES_INVALID  0

#endif
