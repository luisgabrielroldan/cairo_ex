#ifndef DECODE_H
#define DECODE_H

#include "cairo_ex.h"
#include "resmgr.h"
#include <cairo.h>

typedef ei_x_buff cx_result_t;

cx_status_t eio_status();

cx_status_t eio_encode_handle(cx_result_t *buf, cx_res_handle_t handle);

cx_status_t eio_result_free(cx_result_t *result);
cx_status_t eio_encode_result_ok(cx_result_t *result);
cx_status_t eio_encode_result_ok_handle(cx_result_t *result, cx_res_handle_t res);
cx_status_t eio_encode_result_ok_matrix(cx_result_t *result, cairo_matrix_t *matrix);
cx_status_t eio_encode_result_error_atom(cx_result_t *result, const char *atom);
cx_status_t eio_encode_result_ok_tuple_header(cx_result_t *result);

cx_status_t eio_encode_long(cx_result_t *result, long value);
cx_status_t eio_encode_double(cx_result_t *result, double value);
cx_status_t eio_encode_list_header(cx_result_t *result, int arity);
cx_status_t eio_encode_empty_list(cx_result_t *result);

cx_status_t eio_skip_term(const char *buf, int *index);
cx_status_t eio_decode_arg_list(const char *buf, int *index, int nargs);
cx_status_t eio_decode_long(const char *buf, int *index, long *value);
cx_status_t eio_decode_double(const char *buf, int *index, double *value);
cx_status_t eio_decode_atom(const char *buf, int *index, char *dest);
cx_status_t eio_decode_arg_resource(const char *buf, int *index, cx_res_type_t type, void **ref);
cx_status_t eio_decode_list_header(const char *buf, int *index, int *size);

cx_status_t eio_encode_cairo_matrix(cx_result_t *result, cairo_matrix_t *matrix);
cx_status_t eio_decode_cairo_matrix(const char *buf, int *index, cairo_matrix_t *matrix);

cx_status_t eio_decode_double_list(const char *buf, int *index, double **olist, int *len);

cx_status_t eio_decode_str(const char *buf, int *index, char **ref);
void eio_str_free(void *ptr);
#endif
