/* -------------------------------------------

 Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <dvx_core_api.h>
#include <libdvx_global.h>

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