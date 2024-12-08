/* -------------------------------------------

	Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include "dvx_core.h"

extern "C" DVXStreamInterface* dvx_open_preferred_encoder(const char* path_or_url);

/**********************************************************************
 *
 * @brief Opens a stream with path_or_url.
 *
**********************************************************************/
dvx_result_t dvx_open_stream(const char* path_or_url)
{
	DVXStreamInterface* strm = dvx_open_preferred_encoder(path_or_url);

    if (!strm)
    {
        throw DVXException("Out of memory");
    }

    if (strm->IsLocked())
    {
        if (!path_or_url)
        {
            throw DVXException("URL is not provided. (URL required: YES)");
        }

        throw DVXException("URL is not correct. (URL required: YES)");
    }

	if (!strm->InitStreamDVX())
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
 * @brief C++ constructor method.
 *
**********************************************************************/
DVXStreamInterface::DVXStreamInterface() noexcept = default;

/**********************************************************************
 *
 * @brief C++ destructor method.
 *
**********************************************************************/
DVXStreamInterface::~DVXStreamInterface() noexcept = default;
