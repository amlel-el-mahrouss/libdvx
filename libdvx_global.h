/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef QT_CORE_GLOBAL_H
#define QT_CORE_GLOBAL_H

#include <memory>
#include <algorithm>
#include <utility>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <stdint.h>

#define LIBDVX_PACKED __attribute__((packed))
#define LIBDVX_COMPILER "MinGW C++"

#define LIBDVX_VERSION (0x1000)
#define LIBDVX_SUCCESS (0)
#define LIBDVX_FAILURE (1)
#define LIBDVX_NAME    "DVX Library"

#endif // QT_CORE_GLOBAL_H
