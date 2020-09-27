#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "api.h"

cx_status_t cx_translate(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_scale(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_rotate(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_transform(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_set_matrix(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_get_matrix(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_identity_matrix(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_user_to_device(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_user_to_device_distance(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_device_to_user(const char *buf, int *index, cx_result_t *result);
cx_status_t cx_device_to_user_distance(const char *buf, int *index, cx_result_t *result);

#endif
