/*! ***********************************************************************************************
 *
 * file
 * brief       The  class.
 *
 * version     0.1
 * date        2015/4/16
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
#include "shadowsocksserverlistmodel.h"
#include "ping.h"


ShadowsocksServerListModel::ShadowsocksServerListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}


ShadowsocksServerListModel::~ShadowsocksServerListModel()
{
}


int ShadowsocksServerListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return sss_.count();
}


int ShadowsocksServerListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnCount;
}


QVariant ShadowsocksServerListModel::data(const QModelIndex &index, int role) const
{
    QVariant var;

    if (index.isValid() && role == Qt::DisplayRole)
    {
        const ShadowsocksServer &ss = sss_.at(index.row());

        switch (index.column())
        {
        case IPAddress:
            var = ss.ip;
            break;
        case Port:
            var = ss.port;
            break;
        case Password:
            var = ss.password;
            break;
        case Cipher:
            var = ss.cipher;
            break;
        case PingRTT:
            var = ss.ping;
            break;
        }
    }

    return var;
}


QVariant ShadowsocksServerListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant var;

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case IPAddress:
            var = tr("IP Address");
            break;
        case Port:
            var = tr("Port");
            break;
        case Password:
            var = tr("Password");
            break;
        case Cipher:
            var = tr("Cipher");
            break;
        case PingRTT:
            var = tr("Ping RTT");
            break;
        }
    }

    return var;
}


Qt::ItemFlags ShadowsocksServerListModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index);
}


void ShadowsocksServerListModel::sort(int column, Qt::SortOrder order)
{
}


void ShadowsocksServerListModel::add(const ShadowsocksServer &server)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    sss_.append(server);
    endInsertRows();
}


void ShadowsocksServerListModel::removeAt(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    sss_.removeAt(index);
    endRemoveRows();
}


void ShadowsocksServerListModel::setAt(int index, const ShadowsocksServer &server)
{
    sss_.replace(index, server);
    emit dataChanged(createIndex(index, 0), createIndex(index, ColumnCount - 1));
}


void ShadowsocksServerListModel::reset(const ShadowsocksServerList &list)
{
    beginResetModel();
    sss_ = list;
    endResetModel();

    qDeleteAll(pingers_);
    pingers_.clear();

    foreach (const ShadowsocksServer &ss, list)
    {
        Ping *ping = new Ping(this);
        pingers_.append(ping);
        connect(ping, &Ping::finished, this, &ShadowsocksServerListModel::updatePing);
        ping->ping(ss.ip);
    }
}


void ShadowsocksServerListModel::updatePing(int rtt)
{
    Ping *ping = static_cast<Ping *>(sender());

    if (ping)
    {
        int i = pingers_.indexOf(ping);
        ShadowsocksServer ss = sss_.at(i);
        ss.ping = rtt;
        setAt(i, ss);
    }
}
