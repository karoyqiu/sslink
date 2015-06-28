/*! ***********************************************************************************************
 *
 * \file        qrcode.h
 * \brief       The QRCode class.
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
#ifndef QRCODE_H
#define QRCODE_H

#include "qrcode_global.h"

#include <QBitmap>
#include <QScopedPointer>

class QRCodePrivate;

class QRCODESHARED_EXPORT QRCode
{
    Q_DISABLE_COPY(QRCode)
    Q_DECLARE_PRIVATE(QRCode)

public:
    enum Mode
    {
        Null = -1,
        Numeric,
        Alphanumeric,
        Binary,
        Kanji,
        Structure,
        ECI,
        FNC1First,
        FNC1Second,
        Chinese
    };

    enum ErrorCorrectionLevel
    {
        L,
        M,
        Q,
        H
    };


    explicit QRCode(int version = 0, ErrorCorrectionLevel level = L, bool micro = false);
    virtual ~QRCode();

    QBitmap encode(const QString &string, Mode hint = Binary) const;

private:
    QScopedPointer<QRCodePrivate> d_ptr;
};


#endif // QRCODE_H
