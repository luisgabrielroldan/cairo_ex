#ifndef PATH_H
#define PATH_H

#include "api.h"

cx_status_t cx_move_to(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_line_to(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_arc(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_rectangle(const char *buf, int *index, cx_result_t *result);

#endif
