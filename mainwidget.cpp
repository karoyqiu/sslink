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

#include "sslink.h"
#include "shadowsocksserverlistmodel.h"

#include <QWebSettings>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, [this]()
    {
        SSLink *sslink = new SSLink(Q_NULLPTR, this);
        ui->treeView->setModel(sslink->serverList());
        sslink->login();
    });
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
