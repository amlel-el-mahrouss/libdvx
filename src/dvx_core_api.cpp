/* -------------------------------------------

	Copyright (C) 2024 ELMH GROUP, all rights reserved.

------------------------------------------- */

#include <dvx_core_api.h>

bool dvx_validate_url(const char* url, size_t url_len) noexcept
{
	if (!url_len ||
		!url)
		return false;

	for (size_t index_url = 0UL; index_url < url_len; ++index_url)
	{
		if (url[index_url] == ':')
		{
			++index_url;

			if (url[index_url] == '/')
			{
				++index_url;

                if (url[index_url] == '/')
                    return true;
			}
		}
	}

	std::printf("Not an URL: %s\n", url);

	return false;
}
