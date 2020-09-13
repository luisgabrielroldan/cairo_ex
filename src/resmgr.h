#ifndef RESMGR_H
#define RESMGR_H

#include "cairo_ex.h"

#define CX_RESOURCE_NOT_FOUND -1
#define CX_RESOURCE_INVALID -2

typedef enum _cx_res_type_t {
    RES_TYPE_SURFACE = 0x01,
    RES_TYPE_CONTEXT,
} cx_res_type_t;

int ei_decode_cx_res(const char *buf, int *index, cx_res_t *res);
int ei_x_encode_cx_res(ei_x_buff *buf, cx_res_t res);

cx_res_t resmgr_register(void *ptr, cx_res_type_t type);
void resmgr_unregister(cx_res_t res);
void * resmgr_get(cx_res_t res, cx_res_type_t type);

#endif
