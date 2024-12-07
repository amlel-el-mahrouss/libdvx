/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#include "dvx_core_api.h"
#include "dvx_core.h"

/// @brief Implementation of TQ decoding.

#define LIBDVX_COLOR_MAX 255
#define LIBDVX_BLACK_COLOR 0

namespace TQ
{
    /// @brief Stream interface for the TQ algorithm.
    class DVXStreamInterface LIBDVX_STREAM
    {
    public:
        explicit DVXStreamInterface() noexcept;
        virtual ~DVXStreamInterface() noexcept;

        DVXStreamInterface& operator=(const DVXStreamInterface&) = default;
        DVXStreamInterface(const DVXStreamInterface&)			 = default;

        virtual void SetPathOrURL(const char* path_or_url) override;
        virtual bool IsStreaming() noexcept override;
        virtual bool InitStreamDVX() override;
        virtual bool InitDVX() override;
        virtual bool IsLocked() override;
        virtual void FinishDVX() noexcept override;

        virtual void Lock() override;
        virtual void Unlock() override;

    };

    DVXStreamInterface::DVXStreamInterface() noexcept = default;
    DVXStreamInterface::~DVXStreamInterface() noexcept = default;

    namespace Details
    {
        struct DVX_COLOR final
        {
            uint8_t r, g, b;
        };

        bool tq_decode_region(struct DVX_COLOR* in_region, struct DVX_COLOR* out_region, size_t in_region_sz, size_t out_region_sz)
        {
            if (out_region_sz < in_region_sz)
                return false;

            if (!in_region ||
                !out_region)
                return false;

            size_t n_cnt = 0UL;

            for (size_t region_idx = 0; region_idx < in_region_sz; ++region_idx)
            {
                auto diff_r = in_region[region_idx].r - LIBDVX_COLOR_MAX;
                auto diff_g = in_region[region_idx].g - LIBDVX_COLOR_MAX;
                auto diff_b = in_region[region_idx].b - LIBDVX_COLOR_MAX;

                n_cnt = *(uintptr_t*)&in_region[region_idx + 1];
                n_cnt += region_idx;

                for (size_t cnt_index = region_idx; cnt_index < (n_cnt); ++cnt_index)
                {
                    out_region[cnt_index].r = diff_r * LIBDVX_COLOR_MAX;
                    out_region[cnt_index].g = diff_g * LIBDVX_COLOR_MAX;
                    out_region[cnt_index].b = diff_b * LIBDVX_COLOR_MAX;
                }

                ++region_idx;
            }

            return true;
        }
    }
}


extern "C" DVXStreamInterface* dvx_open_platform_stream(const char* url)
{
    ::DVXStreamInterface* interface = new TQ::DVXStreamInterface();

    if (!interface)
        return nullptr;

    interface->SetPathOrURL(url);

    return interface;
}
