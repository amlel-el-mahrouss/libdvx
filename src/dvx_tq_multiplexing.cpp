/* -------------------------------------------

 Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <dvx_format.h>
#include <dvx_stream.h>

namespace TQ::Encoders
{
	enum TQ_REGION_KIND : char
	{
		kRegionInvalid,
		kRegionAudioPCM,
		kRegionVideoRGBA,
		kRegionCount,
	};

	constexpr const char kRegionMagic1 = 0xFF;
	constexpr const char kRegionMagic2 = 0x3F;
	constexpr const char kRegionMagic3 = 0x4F;
	constexpr const char kRegionMagic4_6 = 0x00; // repeat on bit 4, 5 and 6.

	bool tq_demux_region(const char* region, const size_t region_sz, const char* out_audio, size_t* audio_sz, const char* out_video, size_t* video_sz)
	{
		if (!region || !region_sz)
			return false;

		if (!out_audio || !audio_sz)
			return false;

		if (!out_video || !video_sz)
			return false;

		// so we get here PCM and RGBA data.

		return true;
	}
} // namespace TQ
