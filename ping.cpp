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

#ifdef Q_OS_WIN
#include <sdkddkver.h>
#include <qt_windows.h>
#include <ipexport.h>
#include <icmpapi.h>
#include <mstcpip.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

static int pingImpl(const QString &host, int requestSize, int timeout)
{
    Q_UNUSED(requestSize)

    char sendData[32] = "Data buffer.";
    DWORD dwReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(sendData);
    LPVOID pvReplyBuffer = malloc(dwReplySize);
    HANDLE hIcmp = IcmpCreateFile();

    DWORD dwRet = IcmpSendEcho(hIcmp, inet_addr(host.toLocal8Bit().constData()),
                               sendData, sizeof(sendData), NULL, pvReplyBuffer, dwReplySize, timeout);

    if (dwRet != 0)
    {
        PICMP_ECHO_REPLY lpReply = (PICMP_ECHO_REPLY)pvReplyBuffer;
        qDebug() << "Ret" << dwRet << "rtt" << lpReply->RoundTripTime << "status" << lpReply->Status;
        dwRet = lpReply->RoundTripTime;
    }
    else
    {
        qDebug() << "Ret" << dwRet << GetLastError();
        dwRet = std::numeric_limits<int>::max();
    }

    free(pvReplyBuffer);
    IcmpCloseHandle(hIcmp);
    return dwRet;
}

#endif


Ping::Ping(QObject *parent)
    : QObject(parent)
    , size_(32)
    , timeout_(5000)
{
}


Ping::~Ping()
{
}


void Ping::ping(const QString &dest)
{
    QFutureWatcher<int> *watcher = new QFutureWatcher<int>(this);
    connect(watcher, SIGNAL(finished()), this, SLOT(finish()));
    watcher->setFuture(QtConcurrent::run(pingImpl, dest, size_, timeout_));
}


void Ping::setRequestSize(int size)
{
    size_ = size;
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
