/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#include "dvx_core_api.h"
#include "dvx_core.h"

/// @brief Implementation of QT decoding.

#define LIBDVX_COLOR_MAX 255
#define LIBDVX_BLACK_COLOR 0

namespace QT
{
    /// @brief Stream interface for the QT algorithm.
    class DVXStreamInterface LIBDVX_STREAM
    {
    public:
        explicit DVXStreamInterface();

        DVXStreamInterface& operator=(const DVXStreamInterface&) = default;
        DVXStreamInterface(const DVXStreamInterface&)			 = default;

        virtual ~DVXStreamInterface() noexcept;

        virtual void SetPathOrURL(const char* path_or_url) override;
        virtual bool IsStreaming() noexcept override;
        virtual bool InitStreamDVX() override;
        virtual bool InitDVX() override;
        virtual bool IsLocked() override;
        virtual void FinishDVX() noexcept override;

        virtual void Lock() override;
        virtual void Unlock() override;

    };

    DVXStreamInterface::DVXStreamInterface() = default;
    DVXStreamInterface::~DVXStreamInterface() noexcept = default;

    namespace Details
    {
        struct DVX_COLOR
        {
            uint8_t r, g, b;
        };

        bool qt_decode_region(struct DVX_COLOR* region, size_t region_sz)
        {
            size_t n_cnt = 0UL;

            for (size_t region_idx = 0; region_idx < region_sz; ++region_idx)
            {
                auto diff_r = region[region_idx].r - LIBDVX_COLOR_MAX;
                auto diff_g = region[region_idx].g - LIBDVX_COLOR_MAX;
                auto diff_b = region[region_idx].b - LIBDVX_COLOR_MAX;

                n_cnt = *(uintptr_t*)&region[region_idx + 1];
                n_cnt += region_idx;

                for (size_t cnt_index = 0UL; cnt_index < (n_cnt); ++region_idx)
                {
                    region[cnt_index].r = diff_r * LIBDVX_COLOR_MAX;
                    region[cnt_index].g = diff_g * LIBDVX_COLOR_MAX;
                    region[cnt_index].b = diff_b * LIBDVX_COLOR_MAX;
                }
            }

            return true;
        }
    }
}


extern "C" DVXStreamInterface* dvx_open_platform_stream(const char* url)
{
    ::DVXStreamInterface* interface = new QT::DVXStreamInterface();

    if (!interface)
        return nullptr;

    interface->SetPathOrURL(url);

    return interface;
}
