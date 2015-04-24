/*! ***********************************************************************************************
 *
 * \file        main.cpp
 * \brief       The  class.
 *
 * \version     0.1
 * \date        2015/4/24
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
#include <iostream>
#include <QApplication>
#include <QJsonDocument>

#include "ssspider.h"

static SSSpider *spider = Q_NULLPTR;


static void printServers()
{
    spider->deleteLater();

    QJsonDocument doc(toJson(spider->serverList()));
    std::cout << doc.toJson().constData() << std::endl;

    QApplication::quit();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName(QStringLiteral("Q"));
    QApplication::setApplicationName(QStringLiteral("ss-link"));
    QApplication::setApplicationDisplayName(QStringLiteral("SS-Link"));
    QApplication::setApplicationVersion(QStringLiteral("0.3"));
    QApplication::setQuitOnLastWindowClosed(false);

    spider = new SSSpider;
    QObject::connect(spider, &SSSpider::gotServerList, printServers);
    spider->refresh();

    return a.exec();
}
