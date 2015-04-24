/*! ***********************************************************************************************
 *
 * \file        optionsdialog.cpp
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
#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include <QDir>
#include <QMessageBox>
#include <QSettings>


OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    QSettings settings;
    ui->editEmail->setText(settings.value("email").toString());
    ui->editPassword->setText("xXxXxXx");
    ui->spinSocksPort->setValue(settings.value("sslocal/localPort", 1080).toInt());
    ui->comboHttpProxy->setCurrentIndex(settings.value("httpProxy/index", 1).toInt());
    ui->spinHttpPort->setValue(settings.value("httpProxy/port", 8123).toInt());
    ui->checkGlobal->setChecked(!settings.value("httpProxy/localOnly", true).toBool());

    QSettings run("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                  QSettings::NativeFormat);
    ui->checkAutorun->setChecked(run.contains("SS-Link"));
}


OptionsDialog::~OptionsDialog()
{
    delete ui;
}


void OptionsDialog::changeEvent(QEvent *e)
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


void OptionsDialog::accept()
{
    if (ui->editEmail->text().isEmpty())
    {
        QMessageBox::warning(this, QString(), tr("The email cannot be empty."));
        ui->editEmail->setFocus();
        return;
    }

    if (ui->editPassword->text().isEmpty())
    {
        QMessageBox::warning(this, QString(), tr("The password cannot be empty."));
        ui->editPassword->setFocus();
        return;
    }

    QSettings settings;
    settings.setValue("email", ui->editEmail->text());

    if (ui->editPassword->text() != "xXxXxXx")
    {
        settings.setValue("password", qCompress(ui->editPassword->text().toUtf8()));
    }

    settings.setValue("sslocal/localPort", ui->spinSocksPort->value());
    settings.setValue("httpProxy/index", ui->comboHttpProxy->currentIndex());
    settings.setValue("httpProxy/port", ui->spinHttpPort->value());
    settings.setValue("httpProxy/localOnly", !ui->checkGlobal->isChecked());

    QSettings run("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                  QSettings::NativeFormat);

    if (ui->checkAutorun->isChecked())
    {
        run.setValue("SS-Link", QDir::toNativeSeparators(QApplication::applicationFilePath()));
    }
    else
    {
        run.remove("SS-Link");
    }

    QDialog::accept();
}
