/* -------------------------------------------

	Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef DVX_STREAM_H
#define DVX_STREAM_H

/// @brief Digital Video eXtended C++ library.
/// @author Amlal EL Mahrouss.

#include <dvx_core_api.h>
#include <dvx_format.h>

#define LIBDVX_STREAM : public ::DVXStreamInterface

class DVXStreamInterface;

class DVXStreamInterface
{
public:
    explicit DVXStreamInterface() noexcept;
    virtual ~DVXStreamInterface() noexcept;

    DVXStreamInterface& operator=(const DVXStreamInterface&) = default;
    DVXStreamInterface(const DVXStreamInterface&)			 = default;

    virtual void SetPathOrURL(const char* path_or_url) = 0;
    virtual bool IsStreaming() noexcept = 0;
    virtual bool IsPath() noexcept = 0;
    virtual bool InitStreamDVX() = 0;
    virtual bool InitDVX() = 0;
    virtual bool IsLocked() = 0;
    virtual void Finish() noexcept = 0;

    virtual void Lock() = 0;
    virtual void Unlock() = 0;

	virtual bool Decode(size_t out_sz, size_t in_sz, void* in, void* out) = 0;
	virtual bool Encode(size_t out_sz, size_t in_sz, void* in, void* out) = 0;

};

/**********************************************************************
 *
 * @brief Opens a stream with path_or_url.
 *
**********************************************************************/
DVXStreamInterface* dvx_open_stream(const char* path_or_url);

/**********************************************************************
 *
 * @brief Closes stream using it's result.
 *
**********************************************************************/
dvx_error_t dvx_close_stream(DVXStreamInterface* result);

/**********************************************************************
 *
 * @brief Plays the DVX stream.
 *
**********************************************************************/
dvx_error_t dvx_play_stream(DVXStreamInterface* result);

#endif // DVX_STREAM_H
