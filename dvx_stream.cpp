/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#include "dvx_core.h"

/**********************************************************************
 *
 * @brief Opens a stream with path_or_url.
 *
**********************************************************************/
dvx_result_t dvx_open_stream(const char* path_or_url, const char* otp, const void** out_framebuffer)
{
    DVXStream* strm = new DVXStream(path_or_url);

    strm->SetPathOrURL(path_or_url);

    if (strm->IsUrl())
    {
        strm->SetStreamFromWeb(true);
    }

    strm->InitDVX();

    return reinterpret_cast<dvx_result_t>(strm);
}

/**********************************************************************
 *
 * @brief Close stream using it's result.
 *
**********************************************************************/
dvx_error_t dvx_close_result(dvx_result_t result)
{
    DVXStream* strm = (DVXStream*)result;

    if (!strm)
    {
        return LIBDVX_FAILURE;
    }

    if (strm->IsLocked())
    {
        return LIBDVX_FAILURE;
    }

    strm->FinishDVX();

    delete strm;

    return LIBDVX_SUCCESS;
}
