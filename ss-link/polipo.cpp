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
#include "polipo.h"

#include <QtDebug>
#include <QDir>
#include <QProcess>
#include <QSettings>
#include <QTemporaryFile>
#include <QTextStream>

#include "ssproxy.h"


Polipo::Polipo(SSProxy *parent)
    : AbstractHttpProxy(parent)
    , proc_(Q_NULLPTR)
{
}


Polipo::~Polipo()
{
}


void Polipo::start()
{
    if (proc_)
    {
        return;
    }

    QTemporaryFile *config = new QTemporaryFile(QDir::tempPath() + "/polipo-XXXXXX.conf", this);

    if (Q_UNLIKELY(!config->open()))
    {
        qCritical() << "Failed to open temporary file.";
        return;
    }

    QTextStream s(config);

    if (local_)
    {
        s << "proxyAddress = \"127.0.0.1\"" << endl;
    }
    else
    {
        s << "proxyAddress = \"0.0.0.0\"" << endl;
    }

    s << "proxyPort = " << port_ << endl;
    s << "socksParentProxy = \"127.0.0.1:" << parent_->localPort() << "\"" << endl;
    s << "socksProxyType = socks5" << endl;
    s << "diskCacheRoot = \"\"" << endl;
    s << "localDocumentRoot = \"\"" << endl;
    s << "allowedPorts = 1-65535" << endl;
    s << "tunnelAllowedPorts = 1-65535" << endl;

    proc_ = new QProcess(this);
    connect(proc_, &QProcess::stateChanged, this, [this](QProcess::ProcessState state)
    {
        if (state == QProcess::Running)
        {
            emit ready();
        }
    });

    QStringList args;
    args << "-c" << QDir::toNativeSeparators(config->fileName());
    QSettings settings;
    proc_->start(settings.value("httpProxy/polipo", "polipo").toString(), args);
}


void Polipo::stop()
{
    if (proc_)
    {
        proc_->kill();
        proc_->deleteLater();
        proc_ = Q_NULLPTR;
    }
}
