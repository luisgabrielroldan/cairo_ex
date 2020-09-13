#include "context.h"

#include "surface.h"
#include "resmgr.h"
#include "strres.h"

#include <ei.h>
#include <cairo.h>

cx_status_t cx_create(const char *buf, int *index, cx_result_t *result)
{
    int arity;
    cx_res_t surface;
    cairo_surface_t *cairo_surface;
    cairo_t *cairo;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 1) ||
            (ei_decode_cx_res(buf, index, &surface) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    if ((cairo_surface = resmgr_get(surface, RES_TYPE_SURFACE)) == NULL) {
        return CX_RESOURCE_INVALID;
    }

    cairo = cairo_create(cairo_surface);

    if (cairo != NULL) {
        cx_res_t context = resmgr_register(cairo, RES_TYPE_CONTEXT);
        return result_ok_res(result, context);
    }

    cairo_status_t status = cairo_surface_status(NULL);
    return result_error_atom(result, strres_cairo_status_to_str(status));
}

cx_status_t cx_set_source_rgb(const char *buf, int *index, cx_result_t *result)
{
    int arity;
    double r, g, b;
    cx_res_t context;
    cairo_t *cairo;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 4) ||
            (ei_decode_cx_res(buf, index, &context) != 0) ||
            (ei_decode_double(buf, index, &r) != 0) ||
            (ei_decode_double(buf, index, &g) != 0) ||
            (ei_decode_double(buf, index, &b) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    if ((cairo = resmgr_get(context, RES_TYPE_CONTEXT)) == NULL) {
        return CX_RESOURCE_INVALID;
    }

    cairo_set_source_rgb(cairo, r, g, b);

    return result_ok(result);
}

cx_status_t cx_paint(const char *buf, int *index, cx_result_t *result)
{
    int arity;
    cx_res_t context;
    cairo_t *cairo;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 1) ||
            (ei_decode_cx_res(buf, index, &context) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    if ((cairo = resmgr_get(context, RES_TYPE_CONTEXT)) == NULL) {
        return CX_RESOURCE_INVALID;
    }

    cairo_paint(cairo);

    return result_ok(result);
}

cx_status_t cx_set_line_width(const char *buf, int *index, cx_result_t *result)
{
    int arity;
    double width;
    cx_res_t context;
    cairo_t *cairo;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 2) ||
            (ei_decode_cx_res(buf, index, &context) != 0) ||
            (ei_decode_double(buf, index, &width) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    if ((cairo = resmgr_get(context, RES_TYPE_CONTEXT)) == NULL) {
        return CX_RESOURCE_INVALID;
    }

    cairo_set_line_width(cairo, width);

    return result_ok(result);
}

cx_status_t cx_stroke(const char *buf, int *index, cx_result_t *result)
{
    int arity;
    cx_res_t context;
    cairo_t *cairo;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 1) ||
            (ei_decode_cx_res(buf, index, &context) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    if ((cairo = resmgr_get(context, RES_TYPE_CONTEXT)) == NULL) {
        return CX_RESOURCE_INVALID;
    }

    cairo_stroke(cairo);

    return result_ok(result);
}

