#ifndef STRRES_H
#define STRRES_H

#include "cairo_ex.h"

#include <cairo.h>

const char *strres_cairo_status_to_str(cairo_status_t format);

cx_status_t strres_cairo_format_from_str(const char *str, cairo_format_t *format);
const char * strres_cairo_format_to_str(cairo_format_t format);

cx_status_t strres_cairo_content_from_str(const char *str, cairo_content_t *content);
const char *strres_cairo_content_to_str(cairo_content_t content);

#endif
