/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#ifndef LIBDVX_H
#define LIBDVX_H

/// @brief Digital Video eXtended codec and container.
/// @author Amlal EL Mahrouss from ELMH GROUP.

#include <unistd.h>
#include <signal.h>
#include <stdint.h>

#define LIBDVX_VERSION 0x1000

typedef uint32_t dvx_result_t;
typedef uint32_t dvx_error_t;

dvx_result_t dvx_open_stream(const char* path_or_url, const char* otp, const void** out_framebuffer);
dvx_error_t dvx_close_result(dvx_result_t result);

dvx_error_t dvx_next_video(dvx_result_t result);
dvx_error_t dvx_prev_video(dvx_result_t result);

dvx_error_t dvx_pause_video(dvx_result_t result);
dvx_error_t dvx_resume_video(dvx_result_t result);

size_t dvx_current_length_video(dvx_result_t result);
size_t dvx_length_video(dvx_result_t result);

const char** dvx_string_metadata_video(dvx_result_t result);

size_t dvx_timestamp_video(dvx_result_t result);

#endif // LIBDVX_H
