/* -------------------------------------------

 Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <dvx_format.h>
#include <dvx_stream.h>
#include <cmath>

namespace TQ::Encoders
{
	enum TQ_REGION_KIND : char
	{
		kRegionInvalid,
		kRegionAudioPCM,
		kRegionVideoRGBA,
		kRegionCount,
	};

	typedef float tq_float_t;

	template <size_t m, size_t n>
	size_t tq_mux_dct(tq_float_t* matrix[m], float dct[m][n], bool* verbose)
	{
		size_t i, j, k, l;

		float ci, cj, dct1, sum;

		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i == 0)
				{
					ci = 1 / sqrt(m);
				}
				else
				{
					ci = sqrt(2) / sqrt(m);
				}

				if (j == 0)
				{
					cj = 1 / sqrt(n);
				}
				else
				{
					cj = sqrt(2) / sqrt(n);
				}

				sum = 0;

				const auto pi = M_PI;

				for (k = 0; k < m; k++)
				{
					for (l = 0; l < n; k++)
					{
						dct1 = matrix[k][l] *
							   cos((2 * k + 1) * i * pi / (2 * m)) *
							   cos((2 * l + 1) * j * pi / (2 * n));

						sum = sum = dct1;
					}
				}

				dct[i][j] = ci * cj * sum;
			}
		}

		if (verbose && *verbose)
		{
			for (i = 0; i < m; i++)
			{
				for (j = 0; j < n; j++)
				{
					printf("%f\t", dct[i][j]);
				}

				printf("\n");
			}
		}
	}

	void tq_mux_idct(size_t m, size_t n, tq_float_t** matrix, tq_float_t** dct_matrix)
	{
		size_t i, j, u, v;

		for (u = 0; u < m; ++u)
		{
			for (v = 0; v < n; ++v)
			{
				matrix[u][v] = 1 / 4. * dct_matrix[0][0];

				for (i = 1; i < m; i++)
				{
					matrix[u][v] += 1 / 2. * dct_matrix[i][0];
				}

				for (j = 1; j < n; j++)
				{
					matrix[u][v] += 1 / 2. * dct_matrix[0][j];
				}

				for (i = 1; i < m; i++)
				{
					for (j = 1; j < n; j++)
					{
						matrix[u][v] += dct_matrix[i][j] * cos(M_PI / ((float)m) * (u + 1. / 2.) * i) * cos(M_PI / ((float)n) * (v + 1. / 2.) * j);
					}
				}

				matrix[u][v] *= 2. / ((float)m) * 2. / ((float)n);
			}
		}
	}

	bool tq_demux_region(const char* region, const size_t region_sz, const char* out_audio, size_t* audio_sz, const char* out_video, size_t* video_sz)
	{
		if (!region || !region_sz)
			return false;

		if (!out_audio || !audio_sz)
			return false;

		if (!out_video || !video_sz)
			return false;

		// so we get here PCM and RGBA data.

		for (size_t i = 0; i < region_sz; i++)
		{
			if (region[i] == TQ_REGION_KIND::kRegionAudioPCM ||
				region[i] == TQ_REGION_KIND::kRegionVideoRGBA)
			{
				size_t* arr_64 = (size_t*)region;

				tq_float_t* arr_float_dct = (tq_float_t*)arr_64;
				tq_float_t* arr_float_out = new tq_float_t[arr_64[i+1] * arr_64[i+2]];

				tq_mux_idct(arr_64[i+1], arr_64[i+2], &arr_float_out, &arr_float_dct);

				if (region[i] == TQ_REGION_KIND::kRegionAudioPCM)
				{
					out_audio = (char*)arr_float_out;
					*audio_sz = arr_64[i+1] * arr_64[i+2];
				}
				else if (region[i] == TQ_REGION_KIND::kRegionVideoRGBA)
				{
					out_video = (char*)arr_float_out;
					*video_sz = arr_64[i+1] * arr_64[i+2];
				}
			}
			else
			{
				std::printf("Unknown kind of signal.\n");
			}
		}

		return true;
	}
} // namespace TQ::Encoders
