#include "path.h"
#include "context.h"
#include "api.h"

#include <cairo.h>

cx_status_t cx_move_to(const char *buf, int *index, cx_result_t *result)
{
    double x, y;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &x) ||
            eio_decode_double(buf, index, &y)) {
        return eio_status();
    }

    cairo_move_to(cairo, x, y);

    return eio_encode_result_ok(result);
}

cx_status_t cx_line_to(const char *buf, int *index, cx_result_t *result)
{
    double x, y;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &x) ||
            eio_decode_double(buf, index, &y)) {
        return eio_status();
    }

    cairo_line_to(cairo, x, y);

    return eio_encode_result_ok(result);
}

cx_status_t cx_arc(const char *buf, int *index, cx_result_t *result)
{
    double xc, yc, radius, angle1, angle2;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 6) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &xc) ||
            eio_decode_double(buf, index, &yc) ||
            eio_decode_double(buf, index, &radius) ||
            eio_decode_double(buf, index, &angle1) ||
            eio_decode_double(buf, index, &angle2))  {
        return eio_status();
    }

    cairo_arc(cairo, xc, yc, radius, angle1, angle2);

    return eio_encode_result_ok(result);
}

cx_status_t cx_rectangle(const char *buf, int *index, cx_result_t *result)
{
    double x, y, width, height;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 5) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &x) ||
            eio_decode_double(buf, index, &y) ||
            eio_decode_double(buf, index, &width) ||
            eio_decode_double(buf, index, &height)) {
        return eio_status();
    }

    cairo_rectangle(cairo, x, y, width, height);

    return eio_encode_result_ok(result);
}
