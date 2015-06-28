/*! ***********************************************************************************************
 *
 * \file        qrcodedialog.h
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
#pragma once
#ifndef QRCODEDIALOG_H
#define QRCODEDIALOG_H

#include <QDialog>

namespace Ui {
class QRCodeDialog;
}

class QRCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QRCodeDialog(const QString &string, QWidget *parent = 0);
    virtual ~QRCodeDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QRCodeDialog *ui;
};


#endif // QRCODEDIALOG_H
