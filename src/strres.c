#include "strres.h"

#include <string.h>

/********************************************************
 * cairo_format_t
 ********************************************************/

#define TABLE_SIZE_CAIRO_FORMAT 7

typedef struct {
    cairo_format_t value;
    const char *name;
} cairo_format_item_t;

static cairo_format_item_t cairo_format_table[TABLE_SIZE_CAIRO_FORMAT] = {
    {CAIRO_FORMAT_INVALID,   "invalid"},
    {CAIRO_FORMAT_ARGB32,    "argb32"},
    {CAIRO_FORMAT_RGB24,     "rgb24"},
    {CAIRO_FORMAT_A8,        "a8"},
    {CAIRO_FORMAT_A1,        "a1"},
    {CAIRO_FORMAT_RGB16_565, "rgb16_565"},
    {CAIRO_FORMAT_RGB30,     "rgb30"},
};


cairo_format_t strres_cairo_format_from_str(const char *str)
{
    for (int i = 0; i < TABLE_SIZE_CAIRO_FORMAT; i++) {
        if (strcmp(cairo_format_table[i].name, str) == 0 ) {
            return cairo_format_table[i].value;
        }
    }

    return CAIRO_FORMAT_INVALID;
}

const char *strres_cairo_format_to_str(cairo_format_t format)
{
    for (int i = 0; i < TABLE_SIZE_CAIRO_FORMAT; i++) {
        if (cairo_format_table[i].value == format) {
            return cairo_format_table[i].name;
        }
    }

    return cairo_format_table[0].name;
}


/********************************************************
 * cairo_status_t
 ********************************************************/

#define TABLE_SIZE_CAIRO_STATUS 40

typedef struct {
    cairo_status_t value;
    const char *name;
} cairo_status_item_t;

static cairo_status_item_t cairo_status_table[TABLE_SIZE_CAIRO_STATUS] = {
    {CAIRO_STATUS_SUCCESS,                     "success"},
    {CAIRO_STATUS_NO_MEMORY,                   "no_memory"},
    {CAIRO_STATUS_INVALID_RESTORE,             "invalid_restore"},
    {CAIRO_STATUS_INVALID_POP_GROUP,           "invalid_pop_group"},
    {CAIRO_STATUS_NO_CURRENT_POINT,            "no_current_point"},
    {CAIRO_STATUS_INVALID_MATRIX,              "invalid_matrix"},
    {CAIRO_STATUS_INVALID_STATUS,              "invalid_status"},
    {CAIRO_STATUS_NULL_POINTER,                "null_pointer"},
    {CAIRO_STATUS_INVALID_STRING,              "invalid_string"},
    {CAIRO_STATUS_INVALID_PATH_DATA,           "invalid_path_data"},
    {CAIRO_STATUS_READ_ERROR,                  "read_error"},
    {CAIRO_STATUS_WRITE_ERROR,                 "write_error"},
    {CAIRO_STATUS_SURFACE_FINISHED,            "surface_finished"},
    {CAIRO_STATUS_SURFACE_TYPE_MISMATCH,       "surface_type_mismatch"},
    {CAIRO_STATUS_PATTERN_TYPE_MISMATCH,       "pattern_type_mismatch"},
    {CAIRO_STATUS_INVALID_CONTENT,             "invalid_content"},
    {CAIRO_STATUS_INVALID_FORMAT,              "invalid_format"},
    {CAIRO_STATUS_INVALID_VISUAL,              "invalid_visual"},
    {CAIRO_STATUS_FILE_NOT_FOUND,              "file_not_found"},
    {CAIRO_STATUS_INVALID_DASH,                "invalid_dash"},
    {CAIRO_STATUS_INVALID_DSC_COMMENT,         "invalid_dsc_comment"},
    {CAIRO_STATUS_INVALID_INDEX,               "invalid_index"},
    {CAIRO_STATUS_CLIP_NOT_REPRESENTABLE,      "clip_not_representable"},
    {CAIRO_STATUS_TEMP_FILE_ERROR,             "temp_file_error"},
    {CAIRO_STATUS_INVALID_STRIDE,              "invalid_stride"},
    {CAIRO_STATUS_FONT_TYPE_MISMATCH,          "font_type_mismatch"},
    {CAIRO_STATUS_USER_FONT_IMMUTABLE,         "user_font_immutable"},
    {CAIRO_STATUS_USER_FONT_ERROR,             "user_font_error"},
    {CAIRO_STATUS_NEGATIVE_COUNT,              "negative_count"},
    {CAIRO_STATUS_INVALID_CLUSTERS,            "invalid_clusters"},
    {CAIRO_STATUS_INVALID_SLANT,               "invalid_slant"},
    {CAIRO_STATUS_INVALID_WEIGHT,              "invalid_weight"},
    {CAIRO_STATUS_INVALID_SIZE,                "invalid_size"},
    {CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED,   "user_font_not_implemented"},
    {CAIRO_STATUS_DEVICE_TYPE_MISMATCH,        "device_type_mismatch"},
    {CAIRO_STATUS_DEVICE_ERROR,                "device_error"},
    {CAIRO_STATUS_INVALID_MESH_CONSTRUCTION,   "invalid_mesh_construction"},
    {CAIRO_STATUS_DEVICE_FINISHED,             "device_finished"},
    {CAIRO_STATUS_JBIG2_GLOBAL_MISSING,        "jbig2_global_missing"},
    {CAIRO_STATUS_LAST_STATUS,                 "last_status"},
};


const char *strres_cairo_status_to_str(cairo_status_t format)
{
    for (int i = 0; i < TABLE_SIZE_CAIRO_STATUS; i++) {
        if (cairo_status_table[i].value == format) {
            return cairo_status_table[i].name;
        }
    }

    return "unknwon";
}
