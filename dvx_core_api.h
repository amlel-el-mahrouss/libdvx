/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#ifndef DVX_CORE_API_H
#define DVX_CORE_API_H

#include "libdvx_global.h"

/// @brief Singleton class.
class QDVXPlayerSingleton;

/// @brief Player interface.
class QIDVXPlayer;

/// @brief Progress printer.
class QDVXProgressPrinter;

/// @brief DVX decoder and renderer class.
class QDVXWidget;

/// @brief RDP stream class.
class QDVXRTMPWidget;

/// @brief DVX stream interface.
class DVXStreamInterface;

using DVXException = std::runtime_error;

bool dvx_validate_url(const char* url) noexcept;

#endif // DVX_CORE_API_H
