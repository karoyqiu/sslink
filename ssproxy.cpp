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


SSProxy::SSProxy(const ShadowsocksServer &server, bool local, QObject *parent)
    : QObject(parent)
    , server_(server)
    , local_(local)
{
}


SSProxy::~SSProxy()
{
}


void SSProxy::start()
{
    startSslocal();
}


void SSProxy::startSslocal()
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
    json.insert("local_port", settings.value("localPort", 1080).toInt());
    json.insert("password", server_.password);
    json.insert("method", server_.method);
    json.insert("timeout", settings.value("timeout", 600).toInt());

    QJsonDocument doc(json);
    config->write(doc.toJson());
    config->flush();
    qDebug() << "sslocal config file:" << config->fileName();

    QProcess *sslocal = new QProcess(this);
    connect(sslocal, &QProcess::stateChanged, this, [this, sslocal](QProcess::ProcessState state)
    {
        if (state == QProcess::Running)
        {
            startPolipo(sslocal);
        }
    });

    QStringList args;
    args << "-c" << QDir::toNativeSeparators(config->fileName());
    sslocal->start(settings.value("sslocal", "sslocal").toString(), args);
}


void SSProxy::startPolipo(QObject *sslocal)
{
    QTemporaryFile *config = new QTemporaryFile(QDir::tempPath() + "/polipo-XXXXXX.conf", sslocal);

    if (Q_UNLIKELY(!config->open()))
    {
        qCritical() << "Failed to open temporary file.";
        return;
    }

    QTextStream s(config);
    QSettings settings;

    if (local_)
    {
        s << "proxyAddress = \"127.0.0.1\"" << endl;
    }
    else
    {
        s << "proxyAddress = \"0.0.0.0\"" << endl;
    }

    s << "proxyPort = " << settings.value("polipo/port", 8123).toInt() << endl;
    s << "socksParentProxy = \"127.0.0.1:" << settings.value("sslocal/localPort", 1080).toInt() << "\"" << endl;
    s << "socksProxyType = socks5" << endl;
    s << "diskCacheRoot = \"\"" << endl;
    s << "localDocumentRoot = \"\"" << endl;
    s << "allowedPorts = 1-65535" << endl;
    s << "tunnelAllowedPorts = 1-65535" << endl;

    QProcess *polipo = new QProcess(sslocal);
    connect(polipo, &QProcess::stateChanged, this, [this](QProcess::ProcessState state)
    {
        if (state == QProcess::Running)
        {
            emit ready();
        }
    });

    QStringList args;
    args << "-c" << QDir::toNativeSeparators(config->fileName());
    polipo->start(settings.value("polipo/polipo", "polipo").toString(), args);
}
