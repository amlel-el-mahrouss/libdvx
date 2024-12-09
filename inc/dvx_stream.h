/* -------------------------------------------

	Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef DVX_STREAM_H
#define DVX_STREAM_H

/// @brief Digital Video eXtended C++ library.
/// @author Amlal EL Mahrouss.

#include <dvx_core_api.h>

#define LIBDVX_STREAM : public ::DVXStreamInterface

struct DVX_CONTAINER;
struct DVX_CONTAINER_HEADER;

class DVXStreamInterface;

#define LIBDVX_CONTAINER_MAGIC (0xDD775)
#define LIBDVX_CONTAINER_VERSION LIBDVX_VERSION

enum class DVXStreamKind : int32_t
{
    kInvalidContainer,
    kDrmContainer,
    kVideoContainer,
    kAudioContainer,
    kSubtitleContainer,
    kContainerCount,
};

LIBDVX_PACKED(struct DVX_CONTAINER final
{
    char c_name[256];
    DVXStreamKind c_type;
    int32_t c_ratio;
    size_t  c_size;
    uintptr_t c_offset;
};)


LIBDVX_PACKED(struct DVX_CONTAINER_HEADER final
{
    int64_t h_magic;
    int32_t h_version;
    int32_t h_type;

    size_t  h_file_size;
    size_t  h_cont_num;
    size_t  h_avg_ratio;

    char h_author[255];
    char h_copyright[255];
    char h_company[255];

    int8_t h_stars_in_5;

    int32_t h_year;
};)

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
