#include "eio.h"

#include <ei.h>

static cx_status_t eio_last_status = CX_STATUS_OK;

static cx_status_t _eio_set_status(cx_status_t status) {
    eio_last_status = status;
    return status;
}

cx_status_t eio_status() {
    return eio_last_status;
}

cx_status_t eio_x_encode_handle(ei_x_buff *buf, cx_res_handle_t handle) {
    if (ei_x_encode_ulong(buf, handle) != 0) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_result_free(cx_result_t *result)
{
    ei_x_free(result);
    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_result_ok(ei_x_buff *result)
{
    if ((ei_x_new_with_version(result) != 0) ||
            (ei_x_encode_atom(result, "ok") != 0)) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_result_ok_handle(ei_x_buff *result, cx_res_handle_t res)
{
    if ((ei_x_new_with_version(result) != 0) ||
            (ei_x_encode_tuple_header(result, 2) != 0) ||
            (ei_x_encode_atom(result, "ok") != 0) ||
            (eio_x_encode_handle(result, res) != 0) ) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_result_ok_tuple(ei_x_buff *result)
{
    if ((ei_x_new_with_version(result) != 0) ||
            (ei_x_encode_tuple_header(result, 2) != 0) ||
            (ei_x_encode_atom(result, "ok") != 0)) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_result_ok_matrix(ei_x_buff *result, cairo_matrix_t *matrix) {
    if ((ei_x_new_with_version(result) != 0) ||
            (ei_x_encode_tuple_header(result, 2) != 0) ||
            (ei_x_encode_atom(result, "ok") != 0) ||
            eio_encode_cairo_matrix(result, matrix)) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_result_error_atom(ei_x_buff *result, const char *atom)
{
    if ((ei_x_new_with_version(result) != 0) ||
            (ei_x_encode_tuple_header(result, 2) != 0) ||
            (ei_x_encode_atom(result, "error") != 0) ||
            (ei_x_encode_atom(result, atom) != 0)) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_decode_long(const char *buf, int *index, long *value) {
    if (ei_decode_long(buf, index, value) != 0) {
        return _eio_set_status(CX_STATUS_DECODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_long(ei_x_buff *result, long value) {
    if (ei_x_encode_long(result, value) != 0) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_list_header(ei_x_buff *result, int arity) {
    if (ei_x_encode_list_header(result, arity) != 0) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_empty_list(ei_x_buff *result) {
    if (ei_x_encode_empty_list(result) != 0) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_decode_double(const char *buf, int *index, double *value) {
    if (ei_decode_double(buf, index, value) != 0) {
        return _eio_set_status(CX_STATUS_DECODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_encode_double(ei_x_buff *result, double value) {
    if (ei_x_encode_double(result, value) != 0) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_decode_atom(const char *buf, int *index, char *dest) {
    if (ei_decode_atom(buf, index, dest) != 0) {
        return _eio_set_status(CX_STATUS_DECODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_decode_arg_list(const char *buf, int *index, int nargs) {
    int arity;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != nargs)) {
        return _eio_set_status(CX_STATUS_DECODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_decode_list_header(const char *buf, int *index, int *size) {
    if (ei_decode_list_header(buf, index, size) != 0) {
        return _eio_set_status(CX_STATUS_DECODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_decode_arg_resource(const char *buf, int *index, cx_res_type_t type, void **ref) {
    cx_res_handle_t handle;
    resmgr_entry_t *entry;

    if (ei_decode_ulong(buf, index, &handle) != 0)
        return _eio_set_status(CX_STATUS_DECODE_ERROR);

    if (resmgr_find_entry_by_handle(handle, type, &entry) != 0) {
        return _eio_set_status(resmgr_status());
    }

    *ref = entry->ref;

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_decode_str(const char *buf, int *index, char **ref) {
    int type, size;
    long len;
    char *str;

    if ((ei_get_type(buf, index, &type, &size) != 0) || type != ERL_BINARY_EXT)
        return _eio_set_status(CX_STATUS_DECODE_ERROR);

    str = (char *)malloc(size + 1);

    if (ei_decode_binary(buf, index, str, &len) != 0) {
        free(str);
        return _eio_set_status(CX_STATUS_DECODE_ERROR);
    }

    *ref = str;

    return _eio_set_status(CX_STATUS_OK);
}

void eio_str_free(void *ptr) {
    free(ptr);
}

cx_status_t eio_encode_cairo_matrix(ei_x_buff *result, cairo_matrix_t *matrix) {
    if ((ei_x_encode_list_header(result, 6) != 0) ||
            eio_encode_double(result, matrix->xx) ||
            eio_encode_double(result, matrix->yx) ||
            eio_encode_double(result, matrix->xy) ||
            eio_encode_double(result, matrix->yy) ||
            eio_encode_double(result, matrix->x0) ||
            eio_encode_double(result, matrix->y0) ||
            ei_x_encode_empty_list(result) ) {
        return _eio_set_status(CX_STATUS_ENCODE_ERROR);
    }

    return _eio_set_status(CX_STATUS_OK);
}

cx_status_t eio_decode_cairo_matrix(const char *buf, int *index, cairo_matrix_t *matrix) {
    int size;
    double xx, xy, x0;
    double yx, yy, y0;

    if (eio_decode_list_header(buf, index, &size))
        return eio_status();

    if (size != 6) return CX_STATUS_DECODE_ERROR;

    if (eio_decode_double(buf, index, &xx)  ||
            eio_decode_double(buf, index, &yx)  ||
            eio_decode_double(buf, index, &xy)  ||
            eio_decode_double(buf, index, &yy)  ||
            eio_decode_double(buf, index, &x0)  ||
            eio_decode_double(buf, index, &y0) ) {
        return eio_status();
    }

    matrix->xx = xx;
    matrix->xy = xy;
    matrix->x0 = x0;
    matrix->yx = yx;
    matrix->yy = yy;
    matrix->y0 = y0;

    return CX_STATUS_OK;
}

