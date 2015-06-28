/*! ***********************************************************************************************
 *
 * \file        mainwidget.cpp
 * \brief       The MainWidget class.
 *
 * \version     0.1
 * \date        2015/4/15
 *
 * \author      Roy QIU (karoyqiu@gmail.com)
 * \copyright   © 2015 Roy QIU.
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
#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QtDebug>
#include <QCloseEvent>
#include <QDateTime>
#include <QJsonDocument>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>

#include "optionsdialog.h"
#include "shadowsocksserverlistmodel.h"

#include "qrcodedialog.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , model_(Q_NULLPTR)
    , tray_(Q_NULLPTR)
    , spider_(Q_NULLPTR)
    , retryTimer_(Q_NULLPTR)
    , checkTimer_(Q_NULLPTR)
    , checker_(Q_NULLPTR)
{
    ui->setupUi(this);

    model_ = new ShadowsocksServerListModel(this);
    ui->treeView->setModel(model_);
    connect(ui->treeView, &QTreeView::doubleClicked,
            model_, &ShadowsocksServerListModel::selectServer);
    connect(ui->buttonQRCode, &QPushButton::clicked, this, &MainWidget::showQRCode);
    connect(ui->buttonRefresh, &QPushButton::clicked, this, &MainWidget::refresh);
    connect(ui->buttonExit, &QPushButton::clicked, qApp, &QApplication::quit);

    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    ui->treeView->header()->restoreState(settings.value("viewGeometry").toByteArray());

    tray_ = new QSystemTrayIcon(windowIcon(), this);
    connect(tray_, &QSystemTrayIcon::activated, this, &MainWidget::handleTrayActivation);
    tray_->setToolTip(QApplication::applicationDisplayName());

    QMenu *menu = new QMenu(this);
    QAction *action = menu->addAction(tr("&Show"), this, SLOT(showUp()));
    menu->setDefaultAction(action);

    action = menu->addAction(tr("&Options..."), this, SLOT(showOptionsDialog()));
    action->setMenuRole(QAction::PreferencesRole);

    menu->addSeparator();
    menu->addAction(tr("&Restart"), this, SLOT(restartApp()));

    action = menu->addAction(tr("E&xit"), qApp, SLOT(quit()));
    action->setMenuRole(QAction::QuitRole);

    tray_->setContextMenu(menu);
    tray_->show();

    retryTimer_ = new QTimer(this);
    retryTimer_->setInterval(1 * 60 * 1000);
    retryTimer_->setSingleShot(true);
    connect(retryTimer_, &QTimer::timeout, this, &MainWidget::refresh);

    checkTimer_ = new QTimer(this);
    checkTimer_->setInterval(60 * 1000);
    checkTimer_->setSingleShot(true);
    connect(checkTimer_, &QTimer::timeout, this, &MainWidget::checkAvailability);
    connect(model_, SIGNAL(currentServerChanged()), checkTimer_, SLOT(start()));
    connect(model_, &ShadowsocksServerListModel::currentServerChanged, this, [this]()
    {
        this->ui->labelLastUpdate->setText(tr("Last update: %1")
                                           .arg(QDateTime::currentDateTime().toString()));
    });

    QTimer::singleShot(1000, this, SLOT(refresh()));
}


MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    QSettings settings;

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;

    case QEvent::WindowStateChange:
        if ((windowState() & Qt::WindowMinimized) && settings.value("hideOnMinimized", true).toBool())
        {
            hide();
        }
        break;

    default:
        break;
    }
}


void MainWidget::closeEvent(QCloseEvent *e)
{
    e->ignore();
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("viewGeometry", ui->treeView->header()->saveState());
    setWindowState(windowState() | Qt::WindowMinimized);
}


void MainWidget::handleTrayActivation(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        showUp();
    }
}


void MainWidget::showUp()
{
    show();
    raise();
    activateWindow();
    setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}


void MainWidget::showOptionsDialog()
{
    OptionsDialog dialog(this);
    dialog.exec();
}


void MainWidget::restartApp()
{
    if (QProcess::startDetached(QApplication::applicationFilePath(), QStringList()))
    {
        QApplication::quit();
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to restart ss-link."));
    }
}


void MainWidget::refresh()
{
    qDebug() << "Refreshing...";
    delete spider_;

    spider_ = new QProcess(this);
    connect(spider_, SIGNAL(finished(int)), this, SLOT(parseSpiderOutput()));

    QSettings settings;
    spider_->start(settings.value("spider", "ssspider").toString(), QStringList());

    retryTimer_->start();
}


void MainWidget::parseSpiderOutput()
{
    auto json = spider_->readAllStandardOutput();
    qDebug() << "Spider:" << json;
    QJsonDocument doc = QJsonDocument::fromJson(json);
    ShadowsocksServerList servers = fromJson(doc.array());
    model_->reset(servers);

    retryTimer_->stop();
    spider_->deleteLater();
    spider_ = Q_NULLPTR;
}


void MainWidget::checkAvailability()
{
    qDebug() << "Checking availability";
    delete checker_;

    const QSettings settings;
    quint16 port = static_cast<quint16>(settings.value("httpProxy/port", 8123).toUInt());

    checker_ = new QProcess(this);
    connect(checker_, SIGNAL(finished(int)), this, SLOT(verifyAvailability(int)));

    checker_->start(settings.value("checker", "sscheck").toString(), {
                        "--proxy-type", "3",
                        "--proxy-host", "127.0.0.1",
                        "--proxy-port", QString::number(port),
                        "https://www.google.com/"
                    });
}


void MainWidget::verifyAvailability(int exitCode)
{
    if (exitCode != 0)
    {
        qWarning() << "It's unavailable now:" << exitCode;
        qWarning() << checker_->readAllStandardError();
        refresh();
    }
    else
    {
        qDebug() << "It's OK.";
        checkTimer_->start();
    }

    checker_->deleteLater();
    checker_ = Q_NULLPTR;
}


void MainWidget::showQRCode()
{
    QRCodeDialog dialog(uri(model_->currentServer()), this);
    dialog.exec();
}
