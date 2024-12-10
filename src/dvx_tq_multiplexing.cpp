/* -------------------------------------------

 Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>

namespace TQ
{
    typedef double tq_audio_track_t;
    typedef uint32_t tq_video_track_t;

    bool tq_demux_region(const char* region, size_t region_sz,
        const char* out_audio, size_t* audio_sz, const char* out_video, size_t* video_sz)
    {
        if (!region || !region_sz)
            return false;

        if (!out_audio)
            return false;

        if (!out_video)
            return false;

        return true;
    }
}
