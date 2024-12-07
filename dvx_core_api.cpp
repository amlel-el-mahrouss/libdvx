/* -------------------------------------------

    Copyright (C) 2024 DVX GROUP, all rights reserved.

------------------------------------------- */

#include "dvx_core_api.h"

bool dvx_validate_url(const char* url, size_t url_len) noexcept
{
    if (!url_len ||
        !url)
        return false;

    for (int index_url = 0; index_url < url_len; ++index_url)
    {
        if (url[index_url] == ':')
        {
            for (; index_url < url_len; ++index_url)
            {
                if (url[index_url] == '/')
                {
                    ++index_url;

                    for (; index_url < url_len; ++index_url)
                    {
                        if (url[index_url] == '/')
                            return true;
                        else
                            return false;

                        break;
                    }

                    return false;
                }

                return false;
            }

            return false;
        }
    }

    return false;
}
