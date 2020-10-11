#include "router.h"
#include "eio.h"
#include "api/context.h"
#include "api/path.h"
#include "api/surface.h"
#include "api/transformations.h"

#include <string.h>

typedef struct {
    const char *name;
    cx_method method;
} method_entry_t;

static method_entry_t method_table[] = {
    // Transformations
    {"device_to_user", cx_device_to_user },
    {"device_to_user_distance", cx_device_to_user_distance },
    {"get_matrix", cx_get_matrix },
    {"identity_matrix", cx_identity_matrix },
    {"rotate", cx_rotate },
    {"scale", cx_scale },
    {"set_matrix", cx_set_matrix },
    {"transform", cx_transform },
    {"translate", cx_translate },
    {"user_to_device", cx_user_to_device },
    {"user_to_device_distance", cx_user_to_device_distance },
    // Drawing
    {"create", cx_create },
    {"destroy", cx_destroy },
    {"fill", cx_fill },
    {"get_target", cx_get_target },
    {"paint", cx_paint },
    {"pop_group", cx_pop_group },
    {"pop_group_to_source", cx_pop_group_to_source },
    {"push_group", cx_push_group },
    {"push_group_with_content", cx_push_group_with_content },
    {"restore", cx_restore },
    {"save", cx_save },
    {"set_line_width", cx_set_line_width },
    {"set_source_rgb", cx_set_source_rgb },
    {"set_source_rgba", cx_set_source_rgba },
    {"set_dash", cx_set_dash },
    {"status", cx_status },
    {"stroke", cx_stroke },
    // Paths
    {"arc", cx_arc },
    {"line_to", cx_line_to },
    {"move_to", cx_move_to },
    {"rectangle", cx_rectangle },
    // Surface
    {"image_surface_create", cx_surface_image_surface_create },
    {"surface_destroy", cx_surface_destroy },
    {"surface_write_to_png", cx_surface_write_to_png },
    {NULL, NULL}
};

static cx_method router_lookup(const char *name) {
    for (method_entry_t *e = method_table; e->name != NULL; ++e) {
        if (!strcmp(e->name, name)) {
            return e->method;
        }
    }

    return NULL;
}

cx_status_t router_handle(const char *buf, size_t _len, cx_result_t *result) {
    cx_status_t err;
    int index = 0;
    int version = 0;
    int arity = 0;
    char method_name[64];
    cx_method method = NULL;

    if ((ei_decode_version(buf, &index, &version) != 0) ||
            (ei_decode_tuple_header(buf, &index, &arity) != 0) ||
            (arity != 2) ||
            (ei_decode_atom(buf, &index, method_name) != 0)) {
        err = CX_STATUS_DECODE_ERROR;
        goto error;
    }

    if ((method = router_lookup(method_name)) != NULL) {
        err = method(buf, &index, result);
    } else {
        err = CX_STATUS_UNKNOWN_METHOD;
    };

error:
    switch(err) {
    case CX_STATUS_INVALID_REFERENCE:
        return eio_encode_result_error_atom(result, "cx_invalid_reference");

    case CX_STATUS_UNKNOWN_METHOD:
        return eio_encode_result_error_atom(result, "cx_unknown_cmd");

    case CX_STATUS_DECODE_ERROR:
        return eio_encode_result_error_atom(result, "cx_decode");

    case CX_STATUS_ENCODE_ERROR:
        return eio_encode_result_error_atom(result, "cx_encode");

    default:
        return err;
    }
}
