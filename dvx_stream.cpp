/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#include "dvx_core.h"
#include <stdio.h>

dvx_result_t dvx_open_stream(const char* path_or_url, const char* otp, const void** out_framebuffer)
{
    DVXStream* strm = new DVXStream();

    return reinterpret_cast<dvx_result_t>(strm);
}

dvx_error_t dvx_close_result(dvx_result_t result)
{
    DVXStream* strm = (DVXStream*)result;

    if (!strm)
    {
        return LIBDVX_FAILURE;
    }

    delete strm;

    return LIBDVX_SUCCESS;
}
