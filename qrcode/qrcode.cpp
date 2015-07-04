/*! ***********************************************************************************************
 *
 * \file        qrcode.cpp
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
#include "qrcode.h"

#include <QPainter>
#include <QSharedPointer>

#include <qrencode.h>


class QRCodePrivate
{
    Q_DECLARE_PUBLIC(QRCode)

public:
    QRCodePrivate()
        : q_ptr(Q_NULLPTR)
        , version(0)
        , level(QRCode::L)
        , micro(false)
    {
    }


public:
    QRCode *q_ptr;

    int version;
    QRCode::ErrorCorrectionLevel level;
    bool micro;
};


QRCode::QRCode(int version, ErrorCorrectionLevel level, bool micro)
    : d_ptr(new QRCodePrivate)
{
    Q_ASSERT(d_ptr);
    d_ptr->q_ptr = this;
    d_ptr->version = version;
    d_ptr->level = level;
    d_ptr->micro = micro;
}


QRCode::~QRCode()
{
}


QBitmap QRCode::encode(const QString &string, QRCode::Mode hint) const
{
    Q_D(const QRCode);
    QBitmap bitmap;

    QSharedPointer<QRcode> code(QRcode_encodeString(string.toLocal8Bit().constData(), d->version,
                                       static_cast<QRecLevel>(d->level),
                                       static_cast<QRencodeMode>(hint), 1),
                                QRcode_free);

    if (code)
    {
        QBitmap qr(code->width, code->width);
        qr.clear();

        QPainter painter(&qr);
        painter.setBrush(QBrush(Qt::color1));
        painter.setPen(Qt::color1);

        quint8 *p = code->data;

        for (int x = 0; x < code->width; x++)
        {
            for (int y = 0; y < code->width; y++)
            {
                if ((*p & 0x1) == 0x1)
                {
                    painter.drawPoint(x, y);
                }

                p++;
            }
        }

        bitmap.swap(qr);
    }

    return bitmap;
}
