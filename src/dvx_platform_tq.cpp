/* -------------------------------------------

 Copyright (C) 2024 ELMH GROUP, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>
#include <filesystem>
#include <fstream>

/// @brief Implementation of TQ decoding.
/// @note TQ stands for Theather Quality.

#define LIBDVX_VIDEO_SOURCE_MAX (255)
#define LIBDVX_BLACK_COLOR 		(0)
#define LIBDVX_WHITE_COLOR		(255)

namespace TQ
{
	namespace Details
	{
		struct DVX_ENCODE_FORMAT final
		{
			uint8_t red_c, green_c, blue_c;
		};

		bool tq_encode_region(struct DVX_ENCODE_FORMAT* in_region, struct DVX_ENCODE_FORMAT* out_region, size_t in_region_sz, size_t out_region_sz)
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

		bool tq_decode_region(struct DVX_ENCODE_FORMAT* in_region, struct DVX_ENCODE_FORMAT* out_region, size_t in_region_sz, size_t out_region_sz)
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

		virtual void SetPathOrURL(const char* path_or_url) override { m_uri_path = path_or_url; }

		virtual bool IsStreaming() noexcept override { return dvx_validate_url(m_uri_path.c_str(), m_uri_path.size()); }

		virtual bool IsPath() noexcept override { return std::filesystem::exists(m_uri_path); }

		virtual bool InitStreamDVX() override
		{
			if (!this->IsStreaming()) return false;
			if (this->IsPath()) return false;

			return true;
		}

		virtual bool InitDVX() override
		{
			if (this->IsStreaming()) return false;
			if (!this->IsPath()) return false;

			return true;
		}

		virtual bool IsLocked() override { return m_locked; }

		virtual void Finish() noexcept override { }

		virtual void Lock() override { m_locked = true; }

		virtual void Unlock() override { m_locked = false; }

		virtual bool Decode(size_t out_sz, size_t in_sz, void* in, void* out) override
		{
			if (!in ||!out) return false;

			this->m_encoded_blob = in;
			this->m_encoded_size = in_sz;

			return Details::tq_decode_region((Details::DVX_ENCODE_FORMAT*)in, (Details::DVX_ENCODE_FORMAT*)out, in_sz, out_sz);
		}

		virtual bool Encode(size_t out_sz, size_t in_sz, void* in, void* out) override
		{
			if (!in ||!out) return false;

			this->m_encoded_blob = out;
			this->m_encoded_size = out_sz;

			return Details::tq_encode_region((Details::DVX_ENCODE_FORMAT*)in, (Details::DVX_ENCODE_FORMAT*)out, in_sz, out_sz);
		}

	private:
		std::string m_uri_path;
		void* m_encoded_blob{nullptr};
		size_t m_encoded_size{0UL};
		size_t m_container_cnt{0UL};
		bool m_locked{false};
		size_t m_file_size{0UL};
		size_t m_avg_ratio{0UL};

	};

	DVXStreamInterface::DVXStreamInterface() noexcept = default;
	DVXStreamInterface::~DVXStreamInterface() noexcept = default;
}

/**********************************************************************
 *
 * @brief Creates a favourite codecs
 * @param url The URL to stream on (channel)
 *
**********************************************************************/

LIBDVX_EXTERN_C DVXStreamInterface* dvx_open_fav_codec(const char* url)
{
	::DVXStreamInterface* interface = new TQ::DVXStreamInterface();

	if (!interface)
		return nullptr;

	interface->SetPathOrURL(url);

	return interface;
}
