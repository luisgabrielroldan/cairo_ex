#include "context.h"
#include "surface.h"
#include "api.h"

#include <cairo.h>

cx_status_t cx_create(const char *buf, int *index, cx_result_t *result)
{
    void *surface;
    cairo_t *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_SURFACE, &surface)) {
        return eio_status();
    }

    if ((cairo = cairo_create(surface)) != NULL) {
        cx_res_handle_t handle = resmgr_register(cairo, RES_TYPE_CONTEXT);
        return eio_encode_result_ok_handle(result, handle);
    }

    cairo_status_t status = cairo_surface_status(NULL);
    return eio_encode_result_error_atom(result, strres_cairo_status_to_str(status));
}

cx_status_t cx_set_source_rgb(const char *buf, int *index, cx_result_t *result)
{
    double r, g, b;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 4) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &r) ||
            eio_decode_double(buf, index, &g) ||
            eio_decode_double(buf, index, &b)) {
        return eio_status();
    }

    cairo_set_source_rgb(cairo, r, g, b);

    return eio_encode_result_ok(result);
}

cx_status_t cx_set_source_rgba(const char *buf, int *index, cx_result_t *result)
{
    double r, g, b, a;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 5) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &r)  ||
            eio_decode_double(buf, index, &g)  ||
            eio_decode_double(buf, index, &b)  ||
            eio_decode_double(buf, index, &a) ) {
        return eio_status();
    }

    cairo_set_source_rgba(cairo, r, g, b, a);

    return eio_encode_result_ok(result);
}

cx_status_t cx_paint(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_paint(cairo);

    return eio_encode_result_ok(result);
}

cx_status_t cx_fill(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_fill(cairo);

    return eio_encode_result_ok(result);
}

cx_status_t cx_set_line_width(const char *buf, int *index, cx_result_t *result)
{
    double width;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 2) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo) ||
            eio_decode_double(buf, index, &width)) {
        return eio_status();
    }

    cairo_set_line_width(cairo, width);

    return eio_encode_result_ok(result);
}

cx_status_t cx_stroke(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_stroke(cairo);

    return eio_encode_result_ok(result);
}

cx_status_t cx_destroy(const char *buf, int *index, cx_result_t *result)
{
    resmgr_entry_t *entry;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    if (resmgr_find_entry_by_ref(cairo, RES_TYPE_CONTEXT, &entry))
        return resmgr_status();

    cairo_destroy(entry->ref);
    resmgr_unregister(entry->handle);
    return eio_encode_result_ok(result);

}

cx_status_t cx_status(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_status_t status = cairo_status(cairo);

    if (status == CAIRO_STATUS_SUCCESS) {
        return eio_encode_result_ok(result);
    } else {
        return eio_encode_result_error_atom(result, strres_cairo_status_to_str(status));
    }
}

cx_status_t cx_save(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_save(cairo);

    return eio_encode_result_ok(result);
}

cx_status_t cx_restore(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_restore(cairo);

    return eio_encode_result_ok(result);
}

cx_status_t cx_get_target(const char *buf, int *index, cx_result_t *result)
{
    cairo_surface_t *cairo_surface;
    resmgr_entry_t *entry;
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1)  ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    if ((cairo_surface = cairo_get_target(cairo)) == NULL) {
        cairo_status_t status = cairo_status(cairo);
        return eio_encode_result_error_atom(result, strres_cairo_status_to_str(status));
    }

    if (resmgr_find_entry_by_ref(cairo_surface, RES_TYPE_SURFACE, &entry)) {
        return resmgr_status();
    }

    return eio_encode_result_ok_handle(result, entry->handle);
}

cx_status_t cx_push_group(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_push_group(cairo);

    return eio_encode_result_ok(result);
}

cx_status_t cx_pop_group(const char *buf, int *index, cx_result_t *result)
{
    void *cairo;

    if (eio_decode_arg_list(buf, index, 1) ||
            eio_decode_arg_resource(buf, index, RES_TYPE_CONTEXT, &cairo)) {
        return eio_status();
    }

    cairo_pop_group(cairo);

    return eio_encode_result_ok(result);
}

