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
#ifndef PING_H
#define PING_H

#include <QObject>


class Ping : public QObject
{
    Q_OBJECT

public:
    explicit Ping(QObject *parent = Q_NULLPTR);
    virtual ~Ping();

public slots:
    void ping(const QString &dest);
    void setTimeout(int timeout);

signals:
    void finished(int rtt);

private slots:
    void finish();

private:
    int timeout_;
};


#endif // PING_H
