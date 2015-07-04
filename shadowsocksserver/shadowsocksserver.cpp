/*! ***********************************************************************************************
 *
 * file
 * brief       The  class.
 *
 * version     0.1
 * date        2015/4/24
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
#include "shadowsocksserver.h"


QJsonObject toJson(const ShadowsocksServer &server)
{
    QJsonObject json;
    json.insert("ip", server.ip);
    json.insert("port", server.port);
    json.insert("password", server.password);
    json.insert("method", server.method);
    json.insert("ping", server.ping);
    return json;
}


ShadowsocksServer fromJson(const QJsonObject &json)
{
    ShadowsocksServer server;
    server.ip = json.value("ip").toString();
    server.port = json.value("port").toInt();
    server.password = json.value("password").toString();
    server.method = json.value("method").toString();
    server.ping = json.value("ping").toInt(std::numeric_limits<int>::max());
    return server;
}


QJsonArray toJson(const ShadowsocksServerList &servers)
{
    QJsonArray array;

    foreach (const ShadowsocksServer &server, servers)
    {
        array.append(toJson(server));
    }

    return array;
}


ShadowsocksServerList fromJson(const QJsonArray &array)
{
    ShadowsocksServerList servers;

    foreach (const QJsonValue &value, array)
    {
        if (value.isObject())
        {
            servers.append(fromJson(value.toObject()));
        }
    }

    return servers;
}


QByteArray uri(const ShadowsocksServer &server)
{
    QString url = QString("%1:%2@%3:%4").arg(server.method, server.password, server.ip).arg(server.port);
    QByteArray bytes = url.toLocal8Bit();
    bytes = "ss://" + bytes.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
    return bytes;
}
