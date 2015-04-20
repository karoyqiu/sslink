/*! ***********************************************************************************************
 *
 * \file        optionsdialog.h
 * \brief       The OptionsDialog class.
 *
 * \version     0.1
 * \date        2015/4/20
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
#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = Q_NULLPTR);
    virtual ~OptionsDialog();

public slots:
    virtual void accept() Q_DECL_OVERRIDE;

protected:
    virtual void changeEvent(QEvent *e) Q_DECL_OVERRIDE;

private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
