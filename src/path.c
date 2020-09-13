#include "path.h"

#include "context.h"
#include "resmgr.h"
#include "strres.h"

#include <ei.h>
#include <cairo.h>

cx_status_t cx_move_to(const char *buf, int *index, cx_result_t *result)
{
    int arity;
    double x, y;
    cx_res_t context;
    cairo_t *cairo;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 3) ||
            (ei_decode_cx_res(buf, index, &context) != 0) ||
            (ei_decode_double(buf, index, &x) != 0) ||
            (ei_decode_double(buf, index, &y) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    if ((cairo = resmgr_get(context, RES_TYPE_CONTEXT)) == NULL) {
        return CX_RESOURCE_INVALID;
    }

    cairo_move_to(cairo, x, y);

    return result_ok(result);
}

cx_status_t cx_line_to(const char *buf, int *index, cx_result_t *result)
{
    int arity;
    double x, y;
    cx_res_t context;
    cairo_t *cairo;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 3) ||
            (ei_decode_cx_res(buf, index, &context) != 0) ||
            (ei_decode_double(buf, index, &x) != 0) ||
            (ei_decode_double(buf, index, &y) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    if ((cairo = resmgr_get(context, RES_TYPE_CONTEXT)) == NULL) {
        return CX_RESOURCE_INVALID;
    }

    cairo_line_to(cairo, x, y);

    return result_ok(result);
}

