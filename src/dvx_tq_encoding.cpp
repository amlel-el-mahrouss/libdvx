/* -------------------------------------------

 Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>
#include <dvx_format.h>
#include <filesystem>

/// @brief Implementation of TQ decoding.
/// @note TQ stands for Theather Quality.

namespace TQ
{
	namespace Encoders
	{
		bool tq_transfer_encoded_region(struct TQ_VIDEO_FORMAT* in_region, struct TQ_VIDEO_FORMAT* out_region, size_t in_region_sz, size_t out_region_sz)
		{
			if (out_region_sz < in_region_sz)
				return false;

			if (!out_region_sz || !in_region_sz)
				return false;

			if (!in_region ||
				!out_region)
				return false;

			size_t n_cnt = 0UL;

			for (size_t region_idx = 0; region_idx < in_region_sz; ++region_idx)
			{
				auto ratio = in_region[region_idx].encode_ratio;
				auto n_cnt = in_region[region_idx].n_cnt;

				auto diff_r = in_region[region_idx].red_c - ratio;
				auto diff_g = in_region[region_idx].green_c - ratio;
				auto diff_b = in_region[region_idx].blue_c - ratio;

				// encode byte.

				out_region[region_idx].red_c   = diff_r;
				out_region[region_idx].green_c = diff_g;
				out_region[region_idx].blue_c  = diff_b;
				out_region[region_idx].alpha_c = in_region[region_idx].alpha_c;

				++region_idx;

				// we get the n_cnt from in.

				out_region[region_idx] = in_region[region_idx];
			}

			return true;
		}

		bool tq_decode_region(struct TQ_VIDEO_FORMAT* in_region, struct TQ_VIDEO_FORMAT_RAW* out_region, size_t in_region_sz, size_t out_region_sz)
		{
			if (out_region_sz < in_region_sz)
				return false;

			if (!out_region_sz || !in_region_sz)
				return false;

			if (!in_region ||
				!out_region)
				return false;

			size_t n_cnt = 0UL;

			for (size_t region_idx = 0; region_idx < in_region_sz; ++region_idx)
			{
				auto ratio = in_region[region_idx].encode_ratio;
				auto n_cnt = in_region[region_idx].n_cnt;

				auto diff_r = in_region[region_idx].red_c;
				auto diff_g = in_region[region_idx].green_c;
				auto diff_b = in_region[region_idx].blue_c;

				// output the data as we are getting n times it.

				for (size_t cnt_index = region_idx; cnt_index < (n_cnt); ++cnt_index)
				{
					out_region[cnt_index].red_c	   = diff_r + ratio;
					out_region[cnt_index].green_c  = diff_g + ratio;
					out_region[cnt_index].blue_c   = diff_b + ratio;
					out_region[region_idx].alpha_c = in_region[region_idx].alpha_c;
				}

				++region_idx;
			}

			return true;
		}
	} // namespace Encoders

	/// @brief Stream interface for the TQ algorithm.
	class TQStreamInterface LIBDVX_STREAM
	{
	public:
		explicit TQStreamInterface() noexcept;
		virtual ~TQStreamInterface() noexcept;

		TQStreamInterface& operator=(const TQStreamInterface&) = default;
		TQStreamInterface(const TQStreamInterface&)			   = default;

		virtual void SetPathOrURL(const char* path_or_url) override
		{
			m_uri_path = path_or_url;
		}

		virtual bool IsStreaming() noexcept override
		{
			return dvx_validate_url(m_uri_path.c_str(), m_uri_path.size());
		}

		virtual bool IsPath() noexcept override
		{
			return std::filesystem::exists(m_uri_path);
		}

		virtual bool InitStreamDVX() override
		{
			if (!this->IsStreaming())
				return false;
			if (this->IsPath())
				return false;

			return true;
		}

		virtual bool InitDVX() override
		{
			if (this->IsStreaming())
				return false;
			if (!this->IsPath())
				return false;

			return true;
		}

		virtual bool IsLocked() override
		{
			return m_locked;
		}

		virtual void Finish() noexcept override
		{
		    if (this->IsLocked())
				return;

		    if (this->m_encoded_blob)
				this->m_encoded_blob = nullptr;

			this->m_encoded_size = 0UL;
			this->m_file_size = 0UL;
			this->m_uri_path = "";
			this->m_avg_ratio = 0UL;
			this->m_container_cnt = 0UL;
		}

		virtual void Lock() override
		{
			m_locked = true;
		}

		virtual void Unlock() override
		{
			m_locked = false;
		}

		virtual bool Decode(size_t out_sz, size_t in_sz, void* in, void* out) override
		{
			if (!in || !out)
				return false;

			if (!in_sz || out_sz)
				return false;

			this->m_encoded_blob = in;
			this->m_encoded_size = in_sz;

			return Encoders::tq_decode_region((Encoders::TQ_VIDEO_FORMAT*)in, (Encoders::TQ_VIDEO_FORMAT_RAW*)out, in_sz, out_sz);
		}

		virtual bool Encode(size_t out_sz, size_t in_sz, void* in, void* out) override
		{
			if (!in || !out)
				return false;

			if (!in_sz || out_sz)
				return false;

			this->m_encoded_blob = out;
			this->m_encoded_size = out_sz;

			// Encoders::tq_encode_region((Encoders::TQ_VIDEO_FORMAT*)in, in_sz);

			return Encoders::tq_transfer_encoded_region((Encoders::TQ_VIDEO_FORMAT*)in, (Encoders::TQ_VIDEO_FORMAT*)out, in_sz, out_sz);
		}

	private:
		std::string m_uri_path{"dsp://nil"};
		void*		m_encoded_blob{nullptr};
		size_t		m_encoded_size{0UL};
		size_t		m_container_cnt{0UL};
		bool		m_locked{false};
		size_t		m_file_size{0UL};
		size_t		m_avg_ratio{0UL};
	};

	TQStreamInterface::TQStreamInterface() noexcept	 = default;
	TQStreamInterface::~TQStreamInterface() noexcept = default;
} // namespace TQ

/**********************************************************************
 *
 * @brief Creates a favourite codecs
 * @param url The URL to stream on (channel)
 *
**********************************************************************/

LIBDVX_EXTERN_C DVXStreamInterface* dvx_open_tq_codec(const char* url)
{
	::DVXStreamInterface* interface = new TQ::TQStreamInterface();

	if (!interface)
		return nullptr;

	interface->SetPathOrURL(url);

	return interface;
}
