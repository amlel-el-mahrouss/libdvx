/* -------------------------------------------

	Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <dvx_core_api.h>
#include <iostream>

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

	std::cout << "Not an URL: " << url << "\n";

	return false;
}
