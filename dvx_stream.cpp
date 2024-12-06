/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#include "dvx_core.h"
#include "dvx_core_api.h"

extern "C" DVXStreamInterface* dvx_open_platform_stream(const char* otp, const void** out_framebuffer);

/**********************************************************************
 *
 * @brief Opens a stream with path_or_url.
 *
**********************************************************************/
dvx_result_t dvx_open_stream(const char* path_or_url, const char* otp, const void** out_framebuffer)
{
    DVXStreamInterface* strm = dvx_open_platform_stream(otp, out_framebuffer);

    if (!strm)
    {
        throw DVXException("OTP is not correct. (OTP required: YES)");
    }

    strm->SetPathOrURL(path_or_url);

    if (strm->IsStreaming())
    {
        strm->InitStreamDVX();
    }
    else
    {
        strm->InitDVX();
    }

    return reinterpret_cast<dvx_result_t>(strm);
}

/**********************************************************************
 *
 * @brief Close stream using it's result.
 *
**********************************************************************/
dvx_error_t dvx_close_stream(dvx_result_t result)
{
    DVXStreamInterface* strm = (DVXStreamInterface*)result;

    if (!strm ||
        strm->IsLocked())
    {
        return LIBDVX_FAILURE;
    }

    strm->Lock();
    strm->FinishDVX();
    strm->Unlock();

    delete strm;

    strm = nullptr;

    return LIBDVX_SUCCESS;
}

/**********************************************************************
 *
 * @brief Checks for a valid stream object.
 *
**********************************************************************/
DVXStreamInterface::operator bool()
{
    return this->f_video_blob && this->f_video_containers_offset && this->f_video_containers_offset[0];
}

/**********************************************************************
 *
 * @brief C++ constructor method.
 *
**********************************************************************/
DVXStreamInterface::DVXStreamInterface() = default;

/**********************************************************************
 *
 * @brief C++ destructor method.
 *
**********************************************************************/
DVXStreamInterface::~DVXStreamInterface() noexcept
{
    delete[] f_video_blob;

    this->f_video_containers_offset = nullptr;
    this->f_video_blob = nullptr;
    this->f_video_blob_sz = 0UL;
    this->f_video_containers_cnt = 0UL;
}
