#ifndef PATH_H
#define PATH_H

#include "cairo_ex.h"
#include "result.h"

cx_status_t cx_move_to(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_line_to(const char *buf, int *index, cx_result_t *result);
#endif
