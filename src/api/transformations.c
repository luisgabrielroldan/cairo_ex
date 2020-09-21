#include "transformations.h"
#include "api.h"

#include <cairo.h>

static cx_status_t decode_cairo_matrix(const char *buf, int *index, cairo_matrix_t *matrix) {
    int size;
    double xx, xy, x0;
    double yx, yy, y0;

    int tmp = *index;
    debug_term(buf, index);
    *index = tmp;

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

cx_status_t cx_transform(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;
    cairo_matrix_t matrix;

    if (eio_decode_arg_list(buf, index, 2) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            decode_cairo_matrix(buf, index, &matrix) ) {
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
