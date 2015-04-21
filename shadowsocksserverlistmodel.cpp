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

#include <QSettings>
#include <QTimer>

#include "ping.h"
#include "ssproxy.h"
#include "polipo.h"
#include "cow.h"
#include "meow.h"


ShadowsocksServerListModel::ShadowsocksServerListModel(QObject *parent)
    : QAbstractListModel(parent)
    , current_(-1)
    , ssproxy_(Q_NULLPTR)
    , httpProxy_(Q_NULLPTR)
    , autoTimer_(Q_NULLPTR)
{
    autoTimer_ = new QTimer(this);
    autoTimer_->setInterval(1000);
    autoTimer_->setSingleShot(true);
    connect(autoTimer_, &QTimer::timeout, this, &ShadowsocksServerListModel::autoSelectServer);
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

    if (index.isValid())
    {
        const ShadowsocksServer &ss = sss_.at(index.row());

        switch (role)
        {
        case Qt::DisplayRole:
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
            case Method:
                var = ss.method;
                break;
            case PingRTT:
                if (ss.ping == std::numeric_limits<int>::max())
                {
                    var = tr("Timeout");
                }
                else
                {
                    var = ss.ping;
                }
                break;
            }
            break;

        case Qt::CheckStateRole:
            if (index.column() == IPAddress)
            {
                var = index.row() == current_ ? Qt::Checked : Qt::Unchecked;
            }
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
        case Method:
            var = tr("Method");
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
    return QAbstractListModel::flags(index) | Qt::ItemIsUserCheckable;
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
    current_ = -1;

    foreach (const ShadowsocksServer &ss, list)
    {
        Ping *ping = new Ping(this);
        pingers_.append(ping);
        connect(ping, &Ping::finished, this, &ShadowsocksServerListModel::updatePing);
        ping->ping(ss.ip);
    }
}


ShadowsocksServer ShadowsocksServerListModel::currentServer() const
{
    ShadowsocksServer ss;

    if (current_ < 0)
    {
        ss.ping = 0;
        ss.port = 0;
    }
    else
    {
        ss = sss_.at(current_);
    }

    return ss;
}


void ShadowsocksServerListModel::autoSelectServer()
{
    int minRtt = std::numeric_limits<int>::max();
    int minIndex = -1;

    for (int i = 0; i < sss_.count(); i++)
    {
        if (sss_.at(i).ping < minRtt)
        {
            minRtt = sss_.at(i).ping;
            minIndex = i;
        }
    }

    if (minIndex != current_)
    {
        selectServer(createIndex(minIndex, 0));
    }
}


void ShadowsocksServerListModel::selectServer(const QModelIndex &index)
{
    if (index.isValid())
    {
        delete ssproxy_;
        ssproxy_ = new SSProxy(sss_.at(index.row()), this);

        QSettings settings;

        switch (settings.value("httpProxy/index", 1).toInt())
        {
        case 1:
            httpProxy_ = new Polipo(ssproxy_);
            break;
        case 2:
            httpProxy_ = new Cow(ssproxy_);
            break;
        case 3:
            httpProxy_ = new Meow(ssproxy_);
            break;
        default:
            httpProxy_ = Q_NULLPTR;
            break;
        }

        if (httpProxy_)
        {
            connect(httpProxy_, &AbstractHttpProxy::ready, this, [this, index]()
            {
                beginResetModel();
                this->current_ = index.row();
                endResetModel();
                emit currentServerChanged();
            });
        }
        else
        {
            connect(ssproxy_, &SSProxy::ready, this, [this, index]()
            {
                beginResetModel();
                this->current_ = index.row();
                endResetModel();
                emit currentServerChanged();
            });
        }

        ssproxy_->start();
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

        autoTimer_->start();
    }
}
