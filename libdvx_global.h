/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef QT_CORE_GLOBAL_H
#define QT_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QT_CORE_LIBRARY)
#define QT_CORE_EXPORT Q_DECL_EXPORT
#else
#define QT_CORE_EXPORT Q_DECL_IMPORT
#endif

#include <stdexcept>

#define LIBDVX_PACKED __attribute__((packed))
#define LIBDVX_COMPILER "MinGW C++"

#define LIBDVX_VERSION (0x1000)
#define LIBDVX_SUCCESS (0)
#define LIBDVX_FAILURE (1)
#define LIBDVX_NAME    "DVX Library"

#endif // QT_CORE_GLOBAL_H
