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

#include <QSettings>
#include <QTimer>
#include <QWebSettings>

#include "sslink.h"
#include "shadowsocksserverlistmodel.h"


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , sslink_(Q_NULLPTR)
{
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    ui->setupUi(this);
    sslink_ = new SSLink(this);
    ui->treeView->setModel(sslink_->serverList());
    connect(ui->treeView, &QTreeView::doubleClicked,
            sslink_->serverList(), &ShadowsocksServerListModel::selectServer);

    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    ui->treeView->restoreGeometry(settings.value("viewGeometry").toByteArray());

    QTimer::singleShot(1000, sslink_, SLOT(login()));
}


MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWidget::closeEvent(QCloseEvent *e)
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("viewGeometry", ui->treeView->saveGeometry());
    QWidget::closeEvent(e);
}
