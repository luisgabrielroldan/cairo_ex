#ifndef RESULT_H
#define RESULT_H

#include "cairo_ex.h"

typedef ei_x_buff cx_result_t;

int result_free(cx_result_t *result);
int result_ok(cx_result_t *result);
int result_ok_res(cx_result_t *result, cx_res_t res);
int result_error_atom(cx_result_t *result, const char *atom);

#endif
