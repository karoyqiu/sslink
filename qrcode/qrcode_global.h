/*! ***********************************************************************************************
 *
 * \file        qrcode_global.h
 * \brief       The  class.
 *
 * \version     0.1
 * \date        2015/6/24
 *
 * \author      Roy QIU (karoyqiu@gmail.com)
 * \copyright   © 2015 Roy QIU.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * email to karoyqiu@gmail.com.
 *
 **************************************************************************************************/
#pragma once

#ifndef QRCODE_GLOBAL_H
#define QRCODE_GLOBAL_H

#include <QtGlobal>

#if defined(QRCODE_LIBRARY)
#  define QRCODESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QRCODESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QRCODE_GLOBAL_H
