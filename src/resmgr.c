#include "resmgr.h"

typedef struct node {
    cx_res_t key;
    void *ref;
    struct node *next;
} resmgr_entry_t;

static uint32_t resmgr_index = 0;

static resmgr_entry_t *resources_list = NULL;

int ei_decode_cx_res(const char *buf, int *index, cx_res_t *res) {
    return ei_decode_ulong(buf, index, res);
}

int ei_x_encode_cx_res(ei_x_buff *buf, cx_res_t res) {
    return ei_x_encode_ulong(buf, res);
}

cx_res_t resmgr_register(void *ptr, cx_res_type_t type) {
    resmgr_entry_t *node = (resmgr_entry_t *)malloc(sizeof(resmgr_entry_t));

    // Compute next key
    resmgr_index += 0x100;
    cx_res_t key = (resmgr_index | (type & 0xFF));

    node->ref = ptr;
    node->key = key;

    if (resources_list == NULL) {
        resources_list = node;
        node->next = NULL;
    } else {
        node->next = resources_list;
        resources_list = node;
    }

    return key;
}

void * resmgr_get(cx_res_t key, cx_res_type_t type) {
    resmgr_entry_t *curr = resources_list;

    // Validate the key with the expected type
    if ((key & 0xFF) != type) return NULL;

    while (curr != NULL && curr->key != key) {
        curr = curr->next;
    }


    if (curr != NULL && curr->key == key) {
        return curr->ref;
    }

    return NULL;
}

void resmgr_unregister(cx_res_t key) {
    resmgr_entry_t *curr = resources_list;
    resmgr_entry_t *prev = NULL;

    while (curr != NULL && curr->key == key)
    {
        resources_list = curr->next;
        free(curr);
        curr = resources_list;
    }

    while (curr != NULL)
    {
        while (curr != NULL && curr->key != key)
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

