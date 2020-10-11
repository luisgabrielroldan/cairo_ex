#ifndef RESMGR_H
#define RESMGR_H

#include "cairo_ex.h"

#define CX_RESOURCE_INVALID -2

typedef struct node {
    cx_res_handle_t handle;
    void *ref;
    struct node *next;
} resmgr_entry_t;

typedef enum _cx_res_type_t {
    RES_TYPE_SURFACE = 0x01,
    RES_TYPE_CONTEXT,
    RES_TYPE_PATTERN,
} cx_res_type_t;

int ei_decode_cx_res(const char *buf, int *index, cx_res_handle_t *handle);
int ei_x_encode_cx_res(ei_x_buff *buf, cx_res_handle_t handle);

cx_status_t resmgr_status();
cx_res_handle_t resmgr_register(void *ptr, cx_res_type_t type);
void resmgr_unregister(cx_res_handle_t handle);

cx_status_t resmgr_find_entry_by_handle(cx_res_handle_t handle, cx_res_type_t type, resmgr_entry_t **entry);
cx_status_t resmgr_find_entry_by_ref(void *ref, cx_res_type_t type, resmgr_entry_t **entry);

#endif
