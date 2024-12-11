/* -------------------------------------------

	Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef DVX_CORE_API_H
#define DVX_CORE_API_H

#include <libdvx_global.h>

/// @brief DVX stream interface.
class DVXStreamInterface;

/// @brief DVX Exception type.
using DVXException = std::runtime_error;

typedef uintptr_t dvx_result_t;
typedef uint32_t dvx_error_t;

bool dvx_validate_url(const char* url, size_t url_len) noexcept;

#endif // DVX_CORE_API_H
