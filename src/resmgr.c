#include "resmgr.h"

static uint32_t resmgr_index = 0;

static resmgr_entry_t *resources_list = NULL;

static cx_status_t resmgr_last_status = CX_STATUS_OK;

static cx_status_t _resmgr_set_status(cx_status_t status) {
    resmgr_last_status = status;
    return status;
}

cx_status_t resmgr_status() {
    return resmgr_last_status;
}

cx_res_handle_t resmgr_register(void *ptr, cx_res_type_t type) {
    resmgr_entry_t *node = (resmgr_entry_t *)malloc(sizeof(resmgr_entry_t));

    // Compute next handle
    resmgr_index += 0x100;
    cx_res_handle_t handle = (resmgr_index | (type & 0xFF));

    node->ref = ptr;
    node->handle = handle;

    if (resources_list == NULL) {
        resources_list = node;
        node->next = NULL;
    } else {
        node->next = resources_list;
        resources_list = node;
    }

    return handle;
}

cx_status_t resmgr_find_entry_by_ref(void *ref, cx_res_type_t type, resmgr_entry_t **entry) {
    resmgr_entry_t *curr = resources_list;

    while (curr != NULL && curr->ref != ref) {
        curr = curr->next;
    }

    if (curr != NULL && curr->ref == ref &&
            ((curr->handle & 0xFF) == type)) {
        *entry = curr;
        return _resmgr_set_status(CX_STATUS_OK);
    }

    return _resmgr_set_status(CX_STATUS_INVALID_REFERENCE);
}

cx_status_t resmgr_find_entry_by_handle(cx_res_handle_t handle, cx_res_type_t type, resmgr_entry_t **entry) {
    resmgr_entry_t *curr = resources_list;

    // Validate the handle with the expected type
    if ((handle & 0xFF) != type)
        return _resmgr_set_status(CX_STATUS_INVALID_REFERENCE);

    while (curr != NULL && curr->handle != handle) {
        curr = curr->next;
    }

    if (curr != NULL && curr->handle == handle) {
        *entry = curr;
        return _resmgr_set_status(CX_STATUS_OK);
    }

    return _resmgr_set_status(CX_STATUS_INVALID_REFERENCE);
}

void resmgr_unregister(cx_res_handle_t handle) {
    resmgr_entry_t *curr = resources_list;
    resmgr_entry_t *prev = NULL;

    while (curr != NULL && curr->handle == handle)
    {
        resources_list = curr->next;
        free(curr);
        curr = resources_list;
    }

    while (curr != NULL)
    {
        while (curr != NULL && curr->handle != handle)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) return;

        prev->next = curr->next;
        free(curr);
        curr = prev->next;
    }
}

