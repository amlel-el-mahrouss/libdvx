/* -------------------------------------------

	Copyright (C) 2024 ELMH GROUP, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>

LIBDVX_EXTERN_C DVXStreamInterface* dvx_open_tq_codec(const char* path_or_url);

/**********************************************************************
 *
 * @brief Opens a stream with path_or_url.
 *
**********************************************************************/

DVXStreamInterface* dvx_open_stream(const char* path_or_url)
{
	DVXStreamInterface* strm = dvx_open_tq_codec(path_or_url);

    if (!strm)
    {
		throw DVXException("Out of system memory, FATAL!");
    }

    if (strm->IsLocked())
    {
        if (!path_or_url)
        {
			std::printf("URL is not provided. (URL required: YES)");
        }

		std::printf("URL is not correct. (URL required: YES)");

		return nullptr;
	}

	if (!strm->InitStreamDVX())
	{
		strm->InitDVX();
	}

    return strm;
}

/**********************************************************************
 *
 * @brief Closes stream using it's result.
 *
**********************************************************************/

dvx_error_t dvx_close_stream(DVXStreamInterface* result)
{
    DVXStreamInterface* strm = result;

    if (!strm ||
        strm->IsLocked())
    {
        return LIBDVX_FAILURE;
    }

    strm->Lock();
    strm->Finish();
    strm->Unlock();

    delete strm;

    strm = nullptr;

    return LIBDVX_SUCCESS;
}

/**********************************************************************
 *
 * @brief Plays the DVX stream.
 *
**********************************************************************/

dvx_error_t dvx_play_stream(DVXStreamInterface* result)
{
    if (!result)
        return LIBDVX_FAILURE;

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
