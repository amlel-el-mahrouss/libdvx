/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#ifndef DVX_CORE_H
#define DVX_CORE_H

/// @brief Digital Video eXtended C++ library.
/// @author Amlal EL Mahrouss from ELMH GROUP.

#include <unistd.h>
#include <stdint.h>

#define LIBDVX_VERSION (0x1000)
#define LIBDVX_SUCCESS (0)
#define LIBDVX_FAILURE (1)
#define LIBDVX_NAME    "DVX Library"

#define LIBDVX_STREAM : public DVXStreamInterface

struct DVX_CONTAINER;

class DVXStreamInterface;

typedef uintptr_t dvx_result_t;
typedef uint32_t dvx_error_t;

typedef char** dvx_metadata_map_t;

struct DVX_CONTAINER final
{
    char c_name[256];
    int32_t c_type;
    int32_t c_ratio;
    size_t  c_size;
    uintptr_t c_offset;
};

class DVXStreamInterface
{
private:
    char* f_video_blob{nullptr};
    size_t f_video_blob_sz{0};

    struct DVX_CONTAINER** f_video_containers_offset{nullptr};
    size_t f_video_containers_cnt{0};

public:
    operator bool();

    explicit DVXStreamInterface();

    DVXStreamInterface& operator=(const DVXStreamInterface&) = default;
    DVXStreamInterface(const DVXStreamInterface&)			 = default;

    virtual ~DVXStreamInterface() noexcept;

    virtual void SetPathOrURL(const char* path_or_url) = 0;
    virtual bool IsStreaming() noexcept = 0;
    virtual bool InitStreamDVX() = 0;
    virtual bool InitDVX() = 0;
    virtual bool IsLocked() = 0;
    virtual void FinishDVX() noexcept = 0;

    virtual void Lock() = 0;
    virtual void Unlock() = 0;

};

enum class DVXStreamKind
{
    kInvalidContainer,
    kDrmContainer,
    kVideoContainer,
    kAudioContainer,
    kSubtitleContainer,
    kContainerCount,
};


/**********************************************************************
 *
 * @brief Opens a stream with path_or_url.
 *
**********************************************************************/
dvx_result_t dvx_open_stream(const char* path_or_url, const char* otp, const void** out_framebuffer);

/**********************************************************************
 *
 * @brief Close stream using it's result.
 *
**********************************************************************/
dvx_error_t dvx_close_stream(dvx_result_t result);

#endif // DVX_CORE_H
