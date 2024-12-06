/* -------------------------------------------

    Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#ifndef QT_CORE_GLOBAL_H
#define QT_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QT_CORE_LIBRARY)
#define QT_CORE_EXPORT Q_DECL_EXPORT
#else
#define QT_CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // QT_CORE_GLOBAL_H
