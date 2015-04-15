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


SSLink::SSLink(QWebPage *page, QObject *parent)
    : QObject(parent)
    , page_(page)
    , stage_(None)
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
}


SSLink::~SSLink()
{
}


void SSLink::setUserName(const QString &value)
{
    QSettings settings;
    settings.setValue(QStringLiteral("username"), value);
}


void SSLink::setPassword(const QString &value)
{
    QSettings settings;
    settings.setValue(QStringLiteral("password"), value);
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

    value = settings.value(QStringLiteral("password")).toString();
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

    QWebElement thead = table.findFirst("thead tr th");

    while (!thead.isNull())
    {
        qDebug() << thead.toPlainText();
        thead = thead.nextSibling();
    }

    stage_ = None;
    qDebug() << "Done.";
}
