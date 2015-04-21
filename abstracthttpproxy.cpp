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
#include "abstracthttpproxy.h"
#include "ssproxy.h"

#include <QSettings>


AbstractHttpProxy::AbstractHttpProxy(SSProxy *parent)
    : QObject(parent)
    , parent_(parent)
    , local_(true)
    , port_(8123)
{
    Q_ASSERT(parent);
    connect(parent, &SSProxy::ready, this, &AbstractHttpProxy::start);

    QSettings settings;
    settings.beginGroup("httpProxy");
    local_ = settings.value("localOnly", true).toBool();
    port_ = settings.value("port", 8123).toInt();
}


AbstractHttpProxy::~AbstractHttpProxy()
{
}


void AbstractHttpProxy::setLocalOnly(bool value)
{
    if (local_ != value)
    {
        local_ = value;
        emit localOnlyChanged(value);
    }
}


bool AbstractHttpProxy::localOnly() const
{
    return local_;
}


void AbstractHttpProxy::setPort(int value)
{
    if (port_ != value)
    {
        port_ = value;
        emit portChanged(value);
    }
}


int AbstractHttpProxy::port() const
{
    return port_;
}
