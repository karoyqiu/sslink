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
#include "ping.h"

#include <QtConcurrent>
#include <QThread>

#ifdef Q_OS_WIN
#include <sdkddkver.h>
#include <qt_windows.h>
#include <ipexport.h>
#include <icmpapi.h>
#include <mstcpip.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

static int pingImpl(const QString &host, int count, int timeout)
{
    char sendData[32] = "Data buffer.";
    DWORD dwReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(sendData);
    LPVOID pvReplyBuffer = malloc(dwReplySize);
    HANDLE hIcmp = IcmpCreateFile();
    int total = 0;

    for (int i = 0; i < count; i++)
    {
        DWORD dwRet = IcmpSendEcho(hIcmp, inet_addr(host.toLocal8Bit().constData()),
                                   sendData, sizeof(sendData), NULL, pvReplyBuffer, dwReplySize, timeout);

        if (dwRet != 0)
        {
            PICMP_ECHO_REPLY lpReply = (PICMP_ECHO_REPLY)pvReplyBuffer;
            qDebug() << "Ping" << host << lpReply->RoundTripTime;
            total += lpReply->RoundTripTime;
        }
        else
        {
            qDebug() << "Ping" << host << "timeout";
            total += std::numeric_limits<int>::max() / count;
        }

        QThread::currentThread()->msleep(timeout / count);
    }

    free(pvReplyBuffer);
    IcmpCloseHandle(hIcmp);
    return total / count;
}

#endif


Ping::Ping(QObject *parent)
    : QObject(parent)
    , timeout_(3000)
{
}


Ping::~Ping()
{
}


void Ping::ping(const QString &dest)
{
    QFutureWatcher<int> *watcher = new QFutureWatcher<int>(this);
    connect(watcher, SIGNAL(finished()), this, SLOT(finish()));
    watcher->setFuture(QtConcurrent::run(pingImpl, dest, 4, timeout_));
}


void Ping::setTimeout(int timeout)
{
    timeout_ = timeout;
}


void Ping::finish()
{
    QFutureWatcher<int> *watcher = static_cast<QFutureWatcher<int> *>(sender());

    if (watcher)
    {
        emit finished(watcher->result());
    }
}
