#include "transformations.h"
#include "api.h"

#include <cairo.h>

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
