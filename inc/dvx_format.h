/* -------------------------------------------

 Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <dvx_core_api.h>
#include <libdvx_global.h>

#define LIBDVX_CONTAINER_MAGIC (0xDD775)
#define LIBDVX_CONTAINER_VERSION LIBDVX_VERSION

struct DVX_CONTAINER;
struct DVX_CONTAINER_HEADER;

enum class DVXStreamKind : int32_t
{
    kInvalidContainer,
    kDrmContainer,
    kVideoContainer,
    kAudioContainer,
    kSubtitleContainer,
    kContainerCount,
};

struct DVX_CONTAINER final
{
    char c_name[256];
    DVXStreamKind c_type;
    int32_t c_ratio;
    size_t  c_size;
    uintptr_t c_offset;
};

struct DVX_CONTAINER_HEADER final
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
};

namespace TQ
{
    namespace Encoders
    {
		struct TQ_VIDEO_FORMAT final
		{
			uint8_t	 encode_ratio;
			uint32_t n_cnt;
			uint8_t	 red_c, green_c, blue_c;
			uint8_t	 alpha_c;
		};

		struct TQ_VIDEO_FORMAT_RAW final
		{
			uint8_t red_c, green_c, blue_c;
			uint8_t alpha_c;
		};
        
		struct TQ_FLOAT64_FORMAT final
		{
			uint8_t	 n_sign;
			uint32_t n_exp;
			uint64_t n_mantissa;
		};

		struct TQ_FLOAT32_FORMAT final
		{
			uint8_t	 n_sign;
			uint32_t n_exp;
			uint32_t n_mantissa;
		};

		union TQ_FLOAT_PACKET {
			TQ_FLOAT32_FORMAT b32;
			TQ_FLOAT64_FORMAT b64;
		};

		union TQ_VIDEO_PACKET {
			TQ_VIDEO_FORMAT std;
		};

		typedef TQ_FLOAT_PACKET tq_audio_packet_t;
		typedef TQ_VIDEO_FORMAT tq_video_packet_t;
    }
}