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
#include "sslink.h"

#include <QtDebug>
#include <QSettings>
#include <QWebElement>
#include <QWebFrame>
#include <QWebPage>

#include "ping.h"
#include "shadowsocksserverlistmodel.h"


SSLink::SSLink(QObject *parent)
    : QObject(parent)
    , page_(Q_NULLPTR)
    , stage_(None)
    , model_(Q_NULLPTR)
{
    if (page_ == Q_NULLPTR)
    {
        page_ = new QWebPage(this);
        Q_CHECK_PTR(page_);
    }

    connect(page_, &QWebPage::loadFinished, this, &SSLink::processPage);
    connect(page_, &QWebPage::loadStarted, this, [this]()
    {
        qDebug() << "Load started:" << page_->mainFrame()->url();
    });

    model_ = new ShadowsocksServerListModel(this);
}


SSLink::~SSLink()
{
}


ShadowsocksServerListModel *SSLink::serverList() const
{
    return model_;
}


void SSLink::setUserName(const QString &value)
{
    QSettings settings;
    settings.setValue(QStringLiteral("username"), value);
}


void SSLink::setPassword(const QString &value)
{
    QSettings settings;
    settings.setValue(QStringLiteral("password"), qCompress(value.toUtf8()));
}


void SSLink::login()
{
    const QSettings settings;
    QString s = settings.value(QStringLiteral("url"), "http://my.ss-link.com/login?redirect=/my/free").toString();
    stage_ = Login;
    page_->mainFrame()->load(QUrl(s));
}


void SSLink::processPage(bool ok)
{
    qDebug() << "Load finished:" << ok << page_->mainFrame()->url();

    if (Q_LIKELY(ok))
    {
        switch (stage_)
        {
        case Login:
            submitLoginForm();
            break;
        case GetFreeAccount:
            parseFreeAccounts();
            break;
        default:
            break;
        }
    }
    else
    {
        qCritical() << "Failed to load web page.";
    }
}


void SSLink::submitLoginForm()
{
    const QSettings settings;
    QWebFrame *f = page_->mainFrame();

    QString selector = settings.value(QStringLiteral("selector/email"), "#email").toString();
    QWebElement elem = f->findFirstElement(selector);

    if (Q_UNLIKELY(elem.isNull()))
    {
        qCritical() << "Failed to find the email element.";
        return;
    }

    QString value = settings.value(QStringLiteral("email")).toString();
    elem.setAttribute(QStringLiteral("value"), value);

    selector = settings.value(QStringLiteral("selector/password"), "#password").toString();
    elem = f->findFirstElement(selector);

    if (Q_UNLIKELY(elem.isNull()))
    {
        qCritical() << "Failed to find the password element.";
        return;
    }

    value = QString::fromUtf8(qUncompress(settings.value(QStringLiteral("password")).toByteArray()));
    elem.setAttribute(QStringLiteral("value"), value);

    selector = settings.value(QStringLiteral("selector/login"), "login").toString();
    f->evaluateJavaScript(selector + ".click()");
    stage_ = GetFreeAccount;
}


void SSLink::parseFreeAccounts()
{
    QWebFrame *f = page_->mainFrame();
    QWebElement table = f->findFirstElement("table");
    Q_ASSERT(!table.isNull());

    QWebElement thead = table.findFirst("thead tr");
    QWebElementCollection tds = thead.findAll("th");
    int ipIndex = -1, portIndex = -1, passwordIndex = -1, cipherIndex = -1;

    for (int i = 0; i < tds.count(); i++)
    {
        auto th = tds.at(i);
        qDebug() << i << th.toPlainText();

        if (th.toPlainText() == QStringLiteral("服务器IP"))
        {
            ipIndex = i;
        }
        else if (th.toPlainText() == QStringLiteral("服务器端口"))
        {
            portIndex = i;
        }
        else if (th.toPlainText() == QStringLiteral("密码"))
        {
            passwordIndex = i;
        }
        else if (th.toPlainText() == QStringLiteral("加密算法"))
        {
            cipherIndex = i;
        }
    }

    Q_ASSERT(ipIndex != -1 && portIndex != -1 && passwordIndex != -1 && cipherIndex != -1);
    qDebug() << "IP:" << ipIndex << ", port:" << portIndex << ", password:" << passwordIndex
             << ", cipher:" << cipherIndex;

    QWebElement tbody = table.findFirst("tbody tr");
    ShadowsocksServerList list;

    while (!tbody.isNull())
    {
        ShadowsocksServer ss;
        tds = tbody.findAll("td");
        ss.ip = tds.at(ipIndex).toPlainText();
        ss.port = tds.at(portIndex).toPlainText().toInt();
        ss.password = tds.at(passwordIndex).toPlainText();
        ss.method = tds.at(cipherIndex).toPlainText();
        ss.ping = std::numeric_limits<int>::max();
        list.append(ss);
        tbody = tbody.nextSibling();
    }

    model_->reset(list);
    stage_ = None;
    qDebug() << "Done.";
    emit gotServerList();
}
