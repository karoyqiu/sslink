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
#ifndef SSSPIDER_H
#define SSSPIDER_H

#include <QObject>
#include "shadowsocksserver.h"

class QWebPage;
class ShadowsocksServerListModel;


class SSSpider : public QObject
{
    Q_OBJECT

    enum Stage
    {
        None,
        Login,
        GetFreeAccount
    };

public:
    explicit SSSpider(QObject *parent = Q_NULLPTR);
    virtual ~SSSpider();

    ShadowsocksServerList serverList() const;

public slots:
    void setUserName(const QString &value);
    void setPassword(const QString &value);

    void refresh();

signals:
    void loggedIn();
    void gotServerList();

private slots:
    void login();
    void processPage(bool ok);

private:
    void submitLoginForm();
    void parseFreeAccounts();

private:
    QWebPage *page_;
    Stage stage_;
    ShadowsocksServerList servers_;
};


#endif // SSSPIDER_H
