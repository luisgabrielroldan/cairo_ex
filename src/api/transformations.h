#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "api.h"

cx_status_t cx_translate(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_scale(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_rotate(const char *buf, int *index, cx_result_t *result);

#endif
