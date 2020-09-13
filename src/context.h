#ifndef CONTEXT_H
#define CONTEXT_H

#include "cairo_ex.h"
#include "result.h"

cx_status_t cx_create(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_set_source_rgb(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_paint(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_set_line_width(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_stroke(const char *buf, int *index, cx_result_t *result);
#endif
