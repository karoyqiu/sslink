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
#ifndef SSLINK_H
#define SSLINK_H

#include <QObject>

class QWebPage;


class SSLink : public QObject
{
    Q_OBJECT

    enum Stage
    {
        None,
        Login,
        GetFreeAccount
    };

public:
    explicit SSLink(QWebPage *page = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~SSLink();

public slots:
    void setUserName(const QString &value);
    void setPassword(const QString &value);

    void login();

signals:
    void loggedIn();

private slots:
    void processPage(bool ok);

private:
    void submitLoginForm();
    void parseFreeAccounts();

private:
    QWebPage *page_;
    Stage stage_;
};


#endif // SSLINK_H
