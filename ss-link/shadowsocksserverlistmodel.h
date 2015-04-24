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
#pragma once
#ifndef SHADOWSOCKSSERVERLISTMODEL_H
#define SHADOWSOCKSSERVERLISTMODEL_H

#include <QAbstractListModel>

#include "shadowsocksserver.h"

class AbstractHttpProxy;
class SSProxy;
class QTimer;


class ShadowsocksServerListModel : public QAbstractListModel
{
    Q_OBJECT

    enum Column
    {
        IPAddress,
        Port,
        Password,
        Method,
        PingRTT,
        ColumnCount
    };

public:
    explicit ShadowsocksServerListModel(QObject *parent = Q_NULLPTR);
    virtual ~ShadowsocksServerListModel();

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    //virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) Q_DECL_OVERRIDE;

    void add(const ShadowsocksServer &server);
    void removeAt(int index);
    void setAt(int index, const ShadowsocksServer &server);
    void reset(const ShadowsocksServerList &list);
    ShadowsocksServer currentServer() const;

public slots:
    void autoSelectServer();
    void selectServer(const QModelIndex &index);

signals:
    void currentServerChanged();

private slots:
    void updatePing(int rtt);

private:
    ShadowsocksServerList sss_;
    QObjectList pingers_;
    int current_;
    SSProxy *ssproxy_;
    AbstractHttpProxy *httpProxy_;
    QTimer *autoTimer_;
};


#endif // SHADOWSOCKSSERVERLISTMODEL_H
