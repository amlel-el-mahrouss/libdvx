/* -------------------------------------------

 Copyright (C) 2024, ELMH GROUP, all rights reserved.

------------------------------------------- */

#ifndef DVX_GLOBAL_H
#define DVX_GLOBAL_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <string>
#include <memory>
#include <stdexcept>

#define LIBDVX_EXTERN_C extern "C"

#ifdef __GNUC__
#define LIBDVX_PACKED( DECL ) DECL __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define LIBDVX_PACKED( DECL ) __pragma( pack(push, 1) ) DECL __pragma( pack(pop))
#endif

#define LIBDVX_COMPILER "MinGW C++"

#define LIBDVX_VERSION (0x1000)
#define LIBDVX_SUCCESS (0)
#define LIBDVX_FAILURE (1)
#define LIBDVX_NAME    "DVX Library"
#define LIBDVX_EXT	   ".dvx"

LIBDVX_EXTERN_C
{
#include <stdint.h>
}

#endif // DVX_GLOBAL_H
