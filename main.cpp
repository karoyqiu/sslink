/*! ***********************************************************************************************
 *
 * \file        main.cpp
 * \brief       The  class.
 *
 * \version     0.1
 * \date        2015/4/15
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
#include <QApplication>
#include <QSettings>

#include "mainwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName(QStringLiteral("Q"));
    QApplication::setApplicationName(QStringLiteral("ss-link"));
    QApplication::setApplicationDisplayName(QStringLiteral("SS-Link"));
    QApplication::setApplicationVersion(QStringLiteral("0.1"));

    MainWidget w;
    QSettings settings;

    if (!settings.value("hideOnStartUp", true).toBool())
    {
        w.show();
    }

    return a.exec();
}
