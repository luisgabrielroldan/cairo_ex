#include "surface.h"
#include "api.h"

#include <cairo.h>

cx_status_t cx_surface_image_surface_create(const char *buf, int *index, cx_result_t *result)
{
    char format_atom[16];
    long width, height;
    const char *status_str;

    if (eio_decode_arg_list(buf, index, 3) ||
            eio_decode_atom(buf, index, format_atom) ||
            eio_decode_long(buf, index, &width) ||
            eio_decode_long(buf, index, &height)) {
        return eio_status();
    }

    cairo_format_t format;
    if (strres_cairo_format_from_str(format_atom, &format) != CX_STATUS_OK)
        return CX_STATUS_DECODE_ERROR;

    cairo_surface_t *cairo_surface = cairo_image_surface_create (format, width, height);

    if (cairo_surface != NULL) {
        cx_res_handle_t surface = resmgr_register(cairo_surface, RES_TYPE_SURFACE);
        return eio_encode_result_ok_handle(result, surface);
    }

    cairo_status_t status = cairo_surface_status(NULL);
    if (strres_cairo_status_to_str(status, &status_str)) {
        return strres_status();
    }

    return eio_encode_result_error_atom(result, status_str);
}

cx_status_t cx_surface_write_to_png (const char *buf, int *index, cx_result_t *result)
{
    cx_status_t err;
    void *ptr;
    cairo_status_t status;
    char *filename = NULL;
    const char *status_str;

    if (eio_decode_arg_list(buf, index, 2) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_SURFACE, &ptr) ||
            eio_decode_str(buf, index, &filename)) {
        err = eio_status();
        goto done;
    }

    err = CX_STATUS_OK;

    if ((status = cairo_surface_write_to_png(ptr, filename)) != CAIRO_STATUS_SUCCESS) {
        if (strres_cairo_status_to_str(status, &status_str)) {
            err = strres_status();
            goto done;
        }

        if (eio_encode_result_error_atom(result, status_str)) {
            err = eio_status();
        }

        goto done;
    }

    err = eio_encode_result_ok(result);

done:
    if (filename != NULL) eio_str_free(filename);
    return err;
}

cx_status_t cx_surface_destroy (const char *buf, int *index, cx_result_t *result)
{
    void *ptr;
    resmgr_entry_t *entry;

    if (eio_decode_arg_list(buf, index, 1) ||
            (eio_decode_arg_resource(buf, index, RES_TYPE_SURFACE, &ptr) != 0)) {
        return eio_status();
    }

    if (!resmgr_find_entry_by_ref(ptr, RES_TYPE_SURFACE, &entry)) {
        resmgr_unregister(entry->handle);
        cairo_surface_destroy(entry->ref);
        return eio_encode_result_ok(result);
    }

    return eio_encode_result_ok(result);
}
