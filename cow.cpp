/*! ***********************************************************************************************
 *
 * file
 * brief       The  class.
 *
 * version     0.1
 * date        2015/4/21
 *
 * author      Roy QIU (karoyqiu@gmail.com)
 * copyright   © 2015 Roy QIU.
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
#include "cow.h"

#include <QtDebug>
#include <QDir>
#include <QProcess>
#include <QSettings>
#include <QTemporaryFile>
#include <QTextStream>

#include "ssproxy.h"


Cow::Cow(SSProxy *parent)
    : AbstractHttpProxy(parent)
    , proc_(Q_NULLPTR)
{
    QSettings settings;
    program_ = settings.value("httpProxy/cow", "cow").toString();
}


Cow::~Cow()
{
}


void Cow::start()
{
    if (proc_)
    {
        return;
    }

    QTemporaryFile *config = new QTemporaryFile(QDir::tempPath() + "/cow-XXXXXX.rc", this);

    if (Q_UNLIKELY(!config->open()))
    {
        qCritical() << "Failed to open temporary file.";
        return;
    }

    QTextStream s(config);
    s << "listen = http://";

    if (local_)
    {
        s << "127.0.0.1:";
    }
    else
    {
        s << "0.0.0.0:";
    }

    s << port_ << endl;
    s << "proxy = socks5://127.0.0.1:" << parent_->localPort() << endl;

    proc_ = new QProcess(this);
    connect(proc_, &QProcess::stateChanged, this, [this](QProcess::ProcessState state)
    {
        if (state == QProcess::Running)
        {
            emit ready();
        }
    });

    connect(proc_, &QProcess::readyRead, this, [this]()
    {
        qDebug() << proc_->readAll();
    });

    QStringList args;
    args << "-rc=" + QDir::toNativeSeparators(config->fileName());
    proc_->start(program_, args);
}


void Cow::stop()
{
    if (proc_)
    {
        proc_->kill();
        proc_->deleteLater();
        proc_ = Q_NULLPTR;
    }
}
