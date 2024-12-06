/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#ifndef DVX_CORE_API_H
#define DVX_CORE_API_H

#include "libdvx_global.h"

/// @brief DVX stream interface.
class DVXStreamInterface;

using DVXException = std::runtime_error;

typedef uintptr_t dvx_result_t;
typedef uint32_t dvx_error_t;

bool dvx_validate_url(const char* url) noexcept;

#endif // DVX_CORE_API_H
