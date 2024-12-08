/* -------------------------------------------

	Copyright (C) 2024 EL Mahrouss Amlal, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>

LIBDVX_EXTERN_C DVXStreamInterface* dvx_open_preferred_encoder(const char* path_or_url);

/**********************************************************************
 *
 * @brief Opens a stream with path_or_url.
 *
**********************************************************************/
dvx_result_t dvx_open_stream(const char* path_or_url) noexcept
{
	DVXStreamInterface* strm = dvx_open_preferred_encoder(path_or_url);

    if (!strm)
    {
		throw DVXException("Out of system memory, fatal");
    }

    if (strm->IsLocked())
    {
        if (!path_or_url)
        {
			std::printf("URL is not provided. (URL required: YES)");
        }

		std::printf("URL is not correct. (URL required: YES)");

		return 0;
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
