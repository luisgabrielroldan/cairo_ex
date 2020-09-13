#ifndef SURFACE_H
#define SURFACE_H

#include "cairo_ex.h"
#include "result.h"

cx_status_t cx_surface_image_surface_create(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_surface_write_to_png (const char *buf, int *index, cx_result_t *result);
cx_status_t cx_surface_destroy (const char *buf, int *index, cx_result_t *result);
#endif
