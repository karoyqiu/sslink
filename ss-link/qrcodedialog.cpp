/*! ***********************************************************************************************
 *
 * \file        qrcodedialog.cpp
 * \brief       The QRCodeDialog class.
 *
 * \version     0.1
 * \date        2015/6/28
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
#include "qrcodedialog.h"
#include "ui_qrcodedialog.h"

#include <qrcode.h>


QRCodeDialog::QRCodeDialog(const QString &string, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QRCodeDialog)
{
    ui->setupUi(this);
    setFixedSize(218, 218);

    QRCode qr(0, QRCode::M);
    ui->labelQRCode->setPixmap(qr.encode(string).scaledToHeight(200));
}


QRCodeDialog::~QRCodeDialog()
{
    delete ui;
}


void QRCodeDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
