#include "transformations.h"
#include "api.h"

#include <cairo.h>

cx_status_t cx_transform(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;
    cairo_matrix_t matrix;

    if (eio_decode_arg_list(buf, index, 2) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_cairo_matrix(buf, index, &matrix) ) {
        return eio_status();
    }

    cairo_transform(cairo, &matrix);

    return eio_encode_result_ok(result);
}

cx_status_t cx_translate(const char *buf, int *index, cx_result_t *result)
{
    double x, y;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &x)  ||
            eio_decode_double(buf, index, &y) ) {
        return eio_status();
    }

    cairo_translate(cairo, x, y);

    return eio_encode_result_ok(result);
}

cx_status_t cx_scale(const char *buf, int *index, cx_result_t *result)
{
    double sx, sy;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &sx)  ||
            eio_decode_double(buf, index, &sy) ) {
        return eio_status();
    }

    cairo_scale(cairo, sx, sy);

    return eio_encode_result_ok(result);
}

cx_status_t cx_rotate(const char *buf, int *index, cx_result_t *result)
{
    double angle;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 2) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &angle) ) {
        return eio_status();
    }

    cairo_rotate(cairo, angle);

    return eio_encode_result_ok(result);
}

cx_status_t cx_get_matrix(const char *buf, int *index, cx_result_t *result)
{
    cairo_matrix_t matrix;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_get_matrix(cairo, &matrix);

    return eio_encode_result_ok_matrix(result, &matrix);
}

cx_status_t cx_set_matrix(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;
    cairo_matrix_t matrix;

    if (eio_decode_arg_list(buf, index, 2) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_cairo_matrix(buf, index, &matrix) ) {
        return eio_status();
    }

    cairo_set_matrix(cairo, &matrix);

    return eio_encode_result_ok(result);
}

cx_status_t cx_identity_matrix(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_identity_matrix(cairo);

    return eio_encode_result_ok(result);
}

cx_status_t cx_user_to_device(const char *buf, int *index, cx_result_t *result)
{
    double x, y;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &x)  ||
            eio_decode_double(buf, index, &y) ) {
        return eio_status();
    }

    cairo_user_to_device(cairo, &x, &y);

    if (eio_encode_result_ok_tuple(result) ||
            eio_encode_list_header(result, 2) ||
            eio_encode_double(result, x) ||
            eio_encode_double(result, y) ||
            eio_encode_empty_list(result)) {
        return eio_status();
    }

    return CX_STATUS_OK;
}

cx_status_t cx_user_to_device_distance(const char *buf, int *index, cx_result_t *result)
{
    double dx, dy;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &dx)  ||
            eio_decode_double(buf, index, &dy) ) {
        return eio_status();
    }

    cairo_user_to_device_distance(cairo, &dx, &dy);

    if (eio_encode_result_ok_tuple(result) ||
            eio_encode_list_header(result, 2) ||
            eio_encode_double(result, dx) ||
            eio_encode_double(result, dy) ||
            eio_encode_empty_list(result)) {
        return eio_status();
    }

    return CX_STATUS_OK;
}

cx_status_t cx_device_to_user(const char *buf, int *index, cx_result_t *result)
{
    double x, y;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &x)  ||
            eio_decode_double(buf, index, &y) ) {
        return eio_status();
    }

    cairo_device_to_user(cairo, &x, &y);

    if (eio_encode_result_ok_tuple(result) ||
            eio_encode_list_header(result, 2) ||
            eio_encode_double(result, x) ||
            eio_encode_double(result, y) ||
            eio_encode_empty_list(result)) {
        return eio_status();
    }

    return CX_STATUS_OK;
}

cx_status_t cx_device_to_user_distance(const char *buf, int *index, cx_result_t *result)
{
    double dx, dy;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &dx)  ||
            eio_decode_double(buf, index, &dy) ) {
        return eio_status();
    }

    cairo_device_to_user_distance(cairo, &dx, &dy);

    if (eio_encode_result_ok_tuple(result) ||
            eio_encode_list_header(result, 2) ||
            eio_encode_double(result, dx) ||
            eio_encode_double(result, dy) ||
            eio_encode_empty_list(result)) {
        return eio_status();
    }

    return CX_STATUS_OK;
}
