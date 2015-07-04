/*! ***********************************************************************************************
 *
 * file
 * brief       The  class.
 *
 * version     0.1
 * date        2015/4/15
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
#ifndef SHADOWSOCKSSERVER_H
#define SHADOWSOCKSSERVER_H

#include <QString>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

typedef struct ShadowsocksServer
{
    QString ip;
    int port;
    QString password;
    QString method;
    int ping;
} ShadowsocksServer;

typedef QList<ShadowsocksServer> ShadowsocksServerList;

QJsonObject toJson(const ShadowsocksServer &server);
QJsonArray toJson(const ShadowsocksServerList &servers);
ShadowsocksServer fromJson(const QJsonObject &json);
ShadowsocksServerList fromJson(const QJsonArray &array);
QByteArray uri(const ShadowsocksServer &server);


#endif // SHADOWSOCKSSERVER_H
