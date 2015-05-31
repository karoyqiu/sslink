/*! ***********************************************************************************************
 *
 * file
 * brief       The  class.
 *
 * version     0.1
 * date        2015/4/19
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
#include "ssproxy.h"

#include <QtDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QSettings>
#include <QTemporaryFile>
#include <QTextStream>
#include <QTimer>


SSProxy::SSProxy(const ShadowsocksServer &server, QObject *parent)
    : QObject(parent)
    , server_(server)
{
}


SSProxy::~SSProxy()
{
}


int SSProxy::localPort() const
{
    QSettings settings;
    return settings.value("sslocal/localPort", 1080).toInt();
}


void SSProxy::start()
{
    QTemporaryFile *config = new QTemporaryFile(QDir::tempPath() + "/ssconfig-XXXXXX.json", this);

    if (Q_UNLIKELY(!config->open()))
    {
        qCritical() << "Failed to open temporary file.";
        return;
    }

    QSettings settings;
    settings.beginGroup("sslocal");

    QJsonObject json;
    json.insert("server", server_.ip);
    json.insert("server_port", server_.port);
    json.insert("local_address", "127.0.0.1");
    json.insert("local_port", settings.value("localPort", 1080).toInt());
    json.insert("password", server_.password);
    json.insert("method", server_.method);
    json.insert("timeout", settings.value("timeout", 60).toInt());

    QJsonDocument doc(json);
    config->write(doc.toJson());
    config->flush();
    qDebug() << "sslocal config file:" << config->fileName();

    QProcess *sslocal = new QProcess(this);
    connect(sslocal, &QProcess::stateChanged, this, [this, sslocal](QProcess::ProcessState state)
    {
        if (state == QProcess::Running)
        {
            QTimer::singleShot(3000, this, SIGNAL(ready()));
        }
    });

    QStringList args;
    args << "-c" << QDir::toNativeSeparators(config->fileName());
    sslocal->start(settings.value("sslocal", "sslocal").toString(), args);
}
