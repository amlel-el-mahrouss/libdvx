/* -------------------------------------------

	Copyright (C) 2024 EL Mahrouss Amlal, all rights reserved.

------------------------------------------- */

#ifndef DVX_STREAM_H
#define DVX_STREAM_H

/// @brief Digital Video eXtended C++ library.
/// @author EL Mahrouss Amlal.

#include <dvx_core_api.h>

#define LIBDVX_STREAM : public ::DVXStreamInterface

struct DVX_CONTAINER;
struct DVX_CONTAINER_HEADER;

class DVXStreamInterface;

enum class DVXStreamKind : int32_t
{
    kInvalidContainer,
    kDrmContainer,
    kVideoContainer,
    kAudioContainer,
    kSubtitleContainer,
    kContainerCount,
};

struct LIBDVX_PACKED DVX_CONTAINER final
{
    char c_name[256];
    DVXStreamKind c_type;
    int32_t c_ratio;
    size_t  c_size;
    uintptr_t c_offset;
};


struct LIBDVX_PACKED DVX_CONTAINER_HEADER final
{
    int32_t h_magic;
    int32_t h_version;

    size_t  h_file_size;
    size_t  h_num_containers;
    size_t  h_avg_ratio;

    DVX_CONTAINER h_film_info;
    DVX_CONTAINER h_author_info;
};

class DVXStreamInterface
{
public:
    explicit DVXStreamInterface() noexcept;
    virtual ~DVXStreamInterface() noexcept;

    DVXStreamInterface& operator=(const DVXStreamInterface&) = default;
    DVXStreamInterface(const DVXStreamInterface&)			 = default;

    virtual void SetPathOrURL(const char* path_or_url) = 0;
    virtual bool IsStreaming() noexcept = 0;
    virtual bool InitStreamDVX() = 0;
    virtual bool InitDVX() = 0;
    virtual bool IsLocked() = 0;
    virtual void FinishDVX() noexcept = 0;

    virtual void Lock() = 0;
    virtual void Unlock() = 0;

	virtual bool Decode(size_t out_sz, size_t in_sz, void* in, void* out) = 0;
	virtual bool Encode(size_t out_sz, size_t in_sz, void* in, void* out) = 0;

	virtual bool Close(const char* write_as) = 0;

};

/**********************************************************************
 *
 * @brief Opens a stream with path_or_url.
 *
**********************************************************************/
dvx_result_t dvx_open_stream(const char* path_or_url) noexcept;

/**********************************************************************
 *
 * @brief Close stream using it's result.
 *
**********************************************************************/
dvx_error_t dvx_close_stream(dvx_result_t result);

#endif // DVX_STREAM_H