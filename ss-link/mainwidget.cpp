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
#include <QJsonDocument>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>

#include "optionsdialog.h"
#include "shadowsocksserverlistmodel.h"


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , model_(Q_NULLPTR)
    , tray_(Q_NULLPTR)
{
    ui->setupUi(this);

    model_ = new ShadowsocksServerListModel(this);
    ui->treeView->setModel(model_);
    connect(ui->treeView, &QTreeView::doubleClicked,
            model_, &ShadowsocksServerListModel::selectServer);
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
    QProcess *spider = new QProcess(this);
    connect(spider, SIGNAL(finished(int)), this, SLOT(parseSpiderOutput()));

    QSettings settings;
    spider->start(settings.value("spider", "ssspider").toString(), QStringList());
}


void MainWidget::parseSpiderOutput()
{
    QProcess *spider = static_cast<QProcess *>(sender());
    Q_ASSERT(spider);

    QJsonDocument doc = QJsonDocument::fromJson(spider->readAllStandardOutput());
    ShadowsocksServerList servers = fromJson(doc.array());
    model_->reset(servers);
}
