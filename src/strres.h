#ifndef STRRES_H
#define STRRES_H

#include "cairo_ex.h"

#include <cairo.h>

cairo_format_t strres_cairo_format_from_str(const char *str);
const char * strres_cairo_format_to_str(cairo_format_t format);
const char *strres_cairo_status_to_str(cairo_status_t format);

#endif
