#include "surface.h"
#include "resmgr.h"
#include "strres.h"

#include <ei.h>
#include <cairo.h>

cx_status_t cx_surface_image_surface_create(const char *buf, int *index, cx_result_t *result)
{
    int arity = 0;
    char format_atom[16];
    long width, height;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 3) ||
            (ei_decode_atom(buf, index, format_atom) != 0) ||
            (ei_decode_long(buf, index, &width) != 0) ||
            (ei_decode_long(buf, index, &height) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    cairo_format_t format = strres_cairo_format_from_str(format_atom);
    cairo_surface_t *cairo_surface = cairo_image_surface_create (format, width, height);

    if (cairo_surface != NULL) {
        cx_res_t surface = resmgr_register(cairo_surface, RES_TYPE_SURFACE);
        return result_ok_res(result, surface);
    }

    cairo_status_t status = cairo_surface_status(NULL);
    return result_error_atom(result, strres_cairo_status_to_str(status));
}

cx_status_t cx_surface_write_to_png (const char *buf, int *index, cx_result_t *result)
{
    cx_status_t err = CX_STATUS_DECODE_ERROR;
    int type, size, arity;
    cx_res_t surface;
    cairo_surface_t *cairo_surface;
    cairo_status_t status;
    char *filename = NULL;
    long len;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 2) ||
            (ei_decode_cx_res(buf, index, &surface) != 0) ||
            (ei_get_type(buf, index, &type, &size) != 0)) {
        goto done;
    }

    filename = (char *)malloc(size + 1);

    if (ei_decode_binary(buf, index, filename, &len) != 0) goto done;

    err = CX_STATUS_OK;

    if ((cairo_surface = resmgr_get(surface, RES_TYPE_SURFACE)) == NULL) {
        err = CX_RESOURCE_INVALID;
        goto done;
    }

    if ((status = cairo_surface_write_to_png(cairo_surface, filename)) != CAIRO_STATUS_SUCCESS) {
        result_error_atom(result, strres_cairo_status_to_str(status));
        goto done;
    }


    err = result_ok(result);

done:
    if (filename != NULL) free(filename);
    return err;
}

cx_status_t cx_surface_destroy (const char *buf, int *index, cx_result_t *result)
{
    cx_res_t surface;
    cairo_surface_t *cairo_surface;
    int arity;

    if ((ei_decode_list_header(buf, index, &arity) != 0) ||
            (arity != 1) ||
            (ei_decode_cx_res(buf, index, &surface) != 0)) {
        return CX_STATUS_DECODE_ERROR;
    }

    if ((cairo_surface = resmgr_get(surface, RES_TYPE_SURFACE)) == NULL) {
        return result_ok(result);
    }

    resmgr_unregister(surface);

    cairo_surface_destroy(cairo_surface);

    return result_ok(result);
}
