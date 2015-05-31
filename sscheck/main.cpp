/*! ***********************************************************************************************
 *
 * \file        main.cpp
 * \brief       The  class.
 *
 * \version     0.1
 * \date        2015/5/31
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
#include <QtDebug>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("Q"));
    QCoreApplication::setApplicationName(QStringLiteral("ss-link"));
    QCoreApplication::setApplicationVersion(QStringLiteral("0.1"));

    qDebug() << QCoreApplication::arguments();

    QCommandLineParser parser;
    parser.setApplicationDescription("Check availability");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", "The destination URL.");

    QCommandLineOption proxyType("proxy-type", "The type of the proxy.", "type", "3");
    parser.addOption(proxyType);

    QCommandLineOption proxyHost("proxy-host", "The host of the proxy.", "host", "127.0.0.1");
    parser.addOption(proxyHost);

    QCommandLineOption proxyPort("proxy-port", "The port of the proxy.", "port", "8123");
    parser.addOption(proxyPort);

    parser.process(app);

    QNetworkProxy proxy;
    proxy.setType(static_cast<QNetworkProxy::ProxyType>(parser.value(proxyType).toInt()));
    proxy.setHostName(parser.value(proxyHost));
    proxy.setPort(static_cast<quint16>(parser.value(proxyPort).toInt()));

    qDebug() << "Proxy:" << proxy.type() << proxy.hostName() << proxy.port();
    qDebug() << "URL:" << parser.positionalArguments().first();

    QNetworkAccessManager nam;
    nam.setProxy(proxy);

    QNetworkReply *reply = nam.head(QNetworkRequest(QUrl(parser.positionalArguments().first())));
    QObject::connect(reply, &QNetworkReply::finished, [reply]()
    {
        qWarning() << reply->errorString();
        QCoreApplication::exit(reply->error());
        reply->deleteLater();
    });

    return QCoreApplication::exec();
}
