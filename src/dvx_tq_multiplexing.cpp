/* -------------------------------------------

 Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <dvx_formats.h>
#include <dvx_stream.h>

namespace TQ::Encoders
{
	bool tq_demux_region(const char* region, size_t region_sz, const char* out_audio, size_t* audio_sz, const char* out_video, size_t* video_sz)
	{
		if (!region || !region_sz)
			return false;

		if (!out_audio || !audio_sz)
			return false;

		if (!out_video || !video_sz)
			return false;

		return true;
	}
} // namespace TQ
