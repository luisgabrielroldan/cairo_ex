#ifndef ROUTER_H
#define ROUTER_H

#include "result.h"

typedef int (*cx_method)(const char *, int *, cx_result_t *);

int router_handle(const char *buffer, size_t _len, cx_result_t *result);

#endif
