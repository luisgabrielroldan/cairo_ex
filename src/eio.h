#ifndef DECODE_H
#define DECODE_H

#include "cairo_ex.h"
#include "resmgr.h"

typedef ei_x_buff cx_result_t;

cx_status_t eio_status();

int eio_x_encode_handle(ei_x_buff *buf, cx_res_handle_t handle);

cx_status_t eio_x_encode_handle(ei_x_buff *buf, cx_res_handle_t handle);

cx_status_t eio_result_free(cx_result_t *result);
cx_status_t eio_encode_result_ok(ei_x_buff *result);
cx_status_t eio_encode_result_ok_handle(ei_x_buff *result, cx_res_handle_t res);
cx_status_t eio_encode_result_error_atom(ei_x_buff *result, const char *atom);

cx_status_t eio_decode_arg_list(const char *buf, int *index, int nargs);
cx_status_t eio_decode_long(const char *buf, int *index, long *value);
cx_status_t eio_decode_double(const char *buf, int *index, double *value);
cx_status_t eio_decode_atom(const char *buf, int *index, char *dest);
cx_status_t eio_decode_arg_resource(const char *buf, int *index, cx_res_type_t type, void **ref);

cx_status_t eio_decode_str(const char *buf, int *index, char **ref);
void eio_str_free(void *ptr);
#endif
