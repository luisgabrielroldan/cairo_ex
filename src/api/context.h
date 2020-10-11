#ifndef CONTEXT_H
#define CONTEXT_H

#include "api.h"

cx_status_t cx_create(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_set_source_rgb(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_set_source_rgba(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_set_dash(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_paint(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_fill(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_set_line_width(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_stroke(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_destroy(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_status(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_save(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_restore(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_get_target(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_push_group(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_pop_group(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_pop_group_to_source(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_push_group_with_content(const char *buf, int *index, cx_result_t *result);

#endif
