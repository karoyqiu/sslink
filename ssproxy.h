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
#pragma once
#ifndef SSPROXY_H
#define SSPROXY_H

#include <QObject>

#include "shadowsocksserver.h"


class SSProxy : public QObject
{
    Q_OBJECT

public:
    explicit SSProxy(const ShadowsocksServer &server, QObject *parent = Q_NULLPTR);
    virtual ~SSProxy();

    int localPort() const;

public slots:
    void start();

signals:
    void ready();

private:
    const ShadowsocksServer server_;
};


#endif // SSPROXY_H
