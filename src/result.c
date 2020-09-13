#include "result.h"
#include "resmgr.h"

int result_free(cx_result_t *result)
{
    ei_x_free(result);
    return CX_STATUS_OK;
}

int result_ok(ei_x_buff *result)
{
    if ((ei_x_new_with_version(result) != 0) ||
            (ei_x_encode_atom(result, "ok") != 0)) {
        return CX_STATUS_ENCODE_ERROR;
    }

    return CX_STATUS_OK;
}

int result_ok_res(ei_x_buff *result, cx_res_t res)
{
    if ((ei_x_new_with_version(result) != 0) ||
            (ei_x_encode_tuple_header(result, 2) != 0) ||
            (ei_x_encode_atom(result, "ok") != 0) ||
            (ei_x_encode_cx_res(result, res) != 0) ) {
        return CX_STATUS_ENCODE_ERROR;
    }

    return CX_STATUS_OK;
}

int result_error_atom(ei_x_buff *result, const char *atom)
{
    if ((ei_x_new_with_version(result) != 0) ||
            (ei_x_encode_tuple_header(result, 2) != 0) ||
            (ei_x_encode_atom(result, "error") != 0) ||
            (ei_x_encode_atom(result, atom) != 0)) {
        return CX_STATUS_ENCODE_ERROR;
    }

    return CX_STATUS_OK;
}
