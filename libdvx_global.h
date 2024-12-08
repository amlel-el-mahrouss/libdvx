/* -------------------------------------------

 Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef DVX_GLOBAL_H
#define DVX_GLOBAL_H

#include <memory>
#include <algorithm>
#include <utility>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <stdint.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define LIBDVX_PACKED __attribute__((packed))
#define LIBDVX_COMPILER "MinGW C++"

#define LIBDVX_VERSION (0x1000)
#define LIBDVX_SUCCESS (0)
#define LIBDVX_FAILURE (1)
#define LIBDVX_NAME    "DVX Library"
#define LIBDVX_EXT ".dvx"

#endif // DVX_GLOBAL_H
