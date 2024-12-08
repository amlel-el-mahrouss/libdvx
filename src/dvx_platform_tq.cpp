/* -------------------------------------------

 Copyright (C) 2024 EL Mahrouss Amlal, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>

/// @brief Implementation of TQ decoding.
/// @note TQ stands for Theather Quality.

#define LIBDVX_VIDEO_SOURCE_MAX 255
#define LIBDVX_BLACK_COLOR 0

namespace TQ
{
	namespace Details
	{
		struct DVX_VIDEO_SOURCE final
		{
			uint8_t red_c, green_c, blue_c;
		};

		struct DVX_AUDIO_SOURCE final
		{
			uint8_t is_left, is_right;

			union
			{
				struct
				{
					uint8_t sign;
					uint16_t exponent;
					uint32_t mantissa;
				} b32;
				struct
				{
					uint8_t sign;
					uint32_t exponent;
					uint64_t mantissa;
				} b64;
			} wave;
		};

		bool tq_encode_region(struct DVX_VIDEO_SOURCE* in_region, struct DVX_VIDEO_SOURCE* out_region, size_t in_region_sz, size_t out_region_sz)
		{
			if (out_region_sz < in_region_sz)
				return false;

			if (!in_region ||
				!out_region)
				return false;

			size_t n_cnt = 0UL;

			for (size_t region_idx = 0; region_idx < in_region_sz; ++region_idx)
			{
				auto diff_r = in_region[region_idx].red_c - LIBDVX_VIDEO_SOURCE_MAX;
				auto diff_g = in_region[region_idx].green_c - LIBDVX_VIDEO_SOURCE_MAX;
				auto diff_b = in_region[region_idx].blue_c - LIBDVX_VIDEO_SOURCE_MAX;

					   // encode byte.

				out_region[region_idx].red_c = diff_r;
				out_region[region_idx].green_c = diff_g;
				out_region[region_idx].blue_c = diff_b;

				++region_idx;

					   // we get the n_cnt from in.

				out_region[region_idx] = in_region[region_idx];
			}

			return true;
		}

		bool tq_decode_region(struct DVX_VIDEO_SOURCE* in_region, struct DVX_VIDEO_SOURCE* out_region, size_t in_region_sz, size_t out_region_sz)
		{
			if (out_region_sz < in_region_sz)
				return false;

			if (!in_region ||
				!out_region)
				return false;

			size_t n_cnt = 0UL;

			for (size_t region_idx = 0; region_idx < in_region_sz; ++region_idx)
			{
				auto diff_r = in_region[region_idx].red_c;
				auto diff_g = in_region[region_idx].green_c;
				auto diff_b = in_region[region_idx].blue_c;

				n_cnt = *(uintptr_t*)&in_region[region_idx + 1];
				n_cnt += region_idx;

					   // output the data as we are getting n times it.

				for (size_t cnt_index = region_idx; cnt_index < (n_cnt); ++cnt_index)
				{
					out_region[cnt_index].red_c = diff_r + LIBDVX_VIDEO_SOURCE_MAX;
					out_region[cnt_index].green_c = diff_g + LIBDVX_VIDEO_SOURCE_MAX;
					out_region[cnt_index].blue_c = diff_b + LIBDVX_VIDEO_SOURCE_MAX;
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

			

			return true;
		}

		virtual bool IsLocked() override { return m_locked; }

		virtual void FinishDVX() noexcept override { }

		virtual void Lock() override { m_locked = true; }

		virtual void Unlock() override { m_locked = false; }

		virtual bool Decode(size_t out_sz, size_t in_sz, void* in, void* out) override
		{
			if (!in ||!out) return false;

			return Details::tq_decode_region((Details::DVX_VIDEO_SOURCE*)in, (Details::DVX_VIDEO_SOURCE*)out, in_sz, out_sz);
		}

		virtual bool Encode(size_t out_sz, size_t in_sz, void* in, void* out) override
		{
			if (!in ||!out) return false;

			return Details::tq_encode_region((Details::DVX_VIDEO_SOURCE*)in, (Details::DVX_VIDEO_SOURCE*)out, in_sz, out_sz);
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


LIBDVX_EXTERN_C DVXStreamInterface* dvx_open_preferred_encoder(const char* url)
{
	::DVXStreamInterface* interface = new TQ::DVXStreamInterface();

	if (!interface)
		return nullptr;

	interface->SetPathOrURL(url);

	return interface;
}
