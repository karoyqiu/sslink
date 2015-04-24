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
#pragma once
#ifndef ABSTRACTHTTPPROXY_H
#define ABSTRACTHTTPPROXY_H

#include <QObject>

class SSProxy;

class AbstractHttpProxy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool localOnly READ localOnly WRITE setLocalOnly NOTIFY localOnlyChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

public:
    explicit AbstractHttpProxy(SSProxy *parent);
    virtual ~AbstractHttpProxy();

    bool localOnly() const;
    int port() const;

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

    void setLocalOnly(bool value = true);
    void setPort(int value);

signals:
    void ready();
    void localOnlyChanged(bool);
    void portChanged(int);

protected:
    SSProxy *parent_;
    bool local_;
    int port_;
};


#endif // ABSTRACTHTTPPROXY_H
