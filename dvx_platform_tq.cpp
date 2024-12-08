/* -------------------------------------------

 Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

extern "C" {
#include <SDL2/SDL.h>
}

#include "dvx_core_api.h"
#include "dvx_core.h"

/// @brief Implementation of TQ decoding.

#define LIBDVX_COLOR_MAX 255
#define LIBDVX_BLACK_COLOR 0

namespace TQ
{
	namespace Details
	{
		struct DVX_COLOR final
		{
			uint8_t r, g, b;
		};

		bool tq_encode_region(struct DVX_COLOR* in_region, struct DVX_COLOR* out_region, size_t in_region_sz, size_t out_region_sz)
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

					   // encode byte.

				out_region[region_idx].r = diff_r;
				out_region[region_idx].g = diff_g;
				out_region[region_idx].b = diff_b;

				++region_idx;

					   // we get the n_cnt from in.

				out_region[region_idx] = in_region[region_idx];
			}

			return true;
		}

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
				auto diff_r = in_region[region_idx].r;
				auto diff_g = in_region[region_idx].g;
				auto diff_b = in_region[region_idx].b;

				n_cnt = *(uintptr_t*)&in_region[region_idx + 1];
				n_cnt += region_idx;

					   // output the data as we are getting n times it.

				for (size_t cnt_index = region_idx; cnt_index < (n_cnt); ++cnt_index)
				{
					out_region[cnt_index].r = diff_r + LIBDVX_COLOR_MAX;
					out_region[cnt_index].g = diff_g + LIBDVX_COLOR_MAX;
					out_region[cnt_index].b = diff_b + LIBDVX_COLOR_MAX;
				}

				++region_idx;
			}

			return true;
		}
	}

	/// @brief Stream interface for the TQ algorithm.
	class DVXStreamInterface LIBDVX_STREAM
	{
	public:
		explicit DVXStreamInterface() noexcept;
		virtual ~DVXStreamInterface() noexcept;

		DVXStreamInterface& operator=(const DVXStreamInterface&) = default;
		DVXStreamInterface(const DVXStreamInterface&)			 = default;

		virtual void SetPathOrURL(const char* path_or_url) override { m_uri = path_or_url; }
		virtual bool IsStreaming() noexcept override { return dvx_validate_url(m_uri.c_str(), m_uri.size()); }

		virtual bool InitStreamDVX() override
		{
			if (!this->IsStreaming()) return false;

			return true;
		}

		virtual bool InitDVX() override
		{
			if (this->IsStreaming()) return false;

			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

			return true;
		}

		virtual bool IsLocked() override { return m_locked; }

		virtual void FinishDVX() noexcept override { SDL_Quit(); }

		virtual void Lock() override { m_locked = true; }

		virtual void Unlock() override { m_locked = false; }

		virtual bool Decode(size_t out_sz, size_t in_sz, void* in, void* out) override
		{
			if (!in ||!out) return false;

			return Details::tq_decode_region((Details::DVX_COLOR*)in, (Details::DVX_COLOR*)out, in_sz, out_sz);
		}

		virtual bool Encode(size_t out_sz, size_t in_sz, void* in, void* out) override
		{
			if (!in ||!out) return false;

			return Details::tq_encode_region((Details::DVX_COLOR*)in, (Details::DVX_COLOR*)out, in_sz, out_sz);
		}

		virtual bool Close(const char* write_as) override
		{
			if (!write_as)
				return false;

			std::string file = write_as;
			file += LIBDVX_EXT;

			return true;
		}

	private:
		std::string m_uri;
		bool m_locked{false};

	};

	DVXStreamInterface::DVXStreamInterface() noexcept = default;
	DVXStreamInterface::~DVXStreamInterface() noexcept = default;
}


extern "C" DVXStreamInterface* dvx_open_preferred_encoder(const char* url)
{
	::DVXStreamInterface* interface = new TQ::DVXStreamInterface();

	if (!interface)
		return nullptr;

	interface->SetPathOrURL(url);

	return interface;
}
