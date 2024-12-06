/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#ifndef DVX_CORE_H
#define DVX_CORE_H

/// @brief Digital Video eXtended codec and container.
/// @author Amlal EL Mahrouss from ELMH GROUP.

#include <unistd.h>
#include <signal.h>
#include <stdint.h>

#define LIBDVX_VERSION (0x1000)
#define LIBDVX_SUCCESS (0)
#define LIBDVX_FAILURE (1)
#define LIBDVX_NAME    "DVX Playback Library"

class DVXObject;
class DVXStream;

typedef uintptr_t dvx_result_t;
typedef uint32_t dvx_error_t;

typedef char** dvx_metadata_map_t;

class DVXStream final
{
private:
    char* f_video_blob{nullptr};
    size_t f_video_blob_sz{0};

    struct DVXObject* f_video_header_offset{nullptr};
    struct DVXObject** f_video_containers_offset{nullptr};

    size_t f_video_containers_cnt{0};

public:
    operator bool()
    {
        return this->f_video_blob && this->f_video_containers_offset && this->f_video_header_offset && this->f_video_containers_offset[0];
    }

    DVXStream() = default;

    DVXStream& operator=(const DVXStream&) = default;
    DVXStream(const DVXStream&)			 = default;

    ~DVXStream() noexcept
    {
        delete[] f_video_blob;

        this->f_video_header_offset = nullptr;
        this->f_video_containers_offset = nullptr;
        this->f_video_blob = nullptr;
        this->f_video_blob_sz = 0UL;
        this->f_video_containers_cnt = 0UL;
    }
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
