/* -------------------------------------------

 Copyright (C) 2024, EL Mahrouss Amlal, all rights reserved.

------------------------------------------- */

#ifndef DVX_GLOBAL_H
#define DVX_GLOBAL_H

extern "C" {
#include <SDL2/SDL.h>
}

#include <unistd.h>
#include <stdint.h>

#define LIBDVX_EXTERN_C extern "C"

#define LIBDVX_PACKED __attribute__((packed))
#define LIBDVX_COMPILER "MinGW C++"

#define LIBDVX_VERSION (0x1000)
#define LIBDVX_SUCCESS (0)
#define LIBDVX_FAILURE (1)
#define LIBDVX_NAME    "DVX Library"
#define LIBDVX_EXT ".dvx"

#endif // DVX_GLOBAL_H
