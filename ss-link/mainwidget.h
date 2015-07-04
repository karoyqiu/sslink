/*! ***********************************************************************************************
 *
 * \file        mainwidget.h
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
#pragma once
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>

namespace Ui {
class MainWidget;
}

class QProcess;
class ShadowsocksServerListModel;


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = Q_NULLPTR);
    virtual ~MainWidget();

protected:
    virtual void changeEvent(QEvent *e) Q_DECL_OVERRIDE;
    virtual void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;

private slots:
    void handleTrayActivation(QSystemTrayIcon::ActivationReason reason);
    void showUp();
    void showOptionsDialog();
    void restartApp();
    void refresh();
    void parseSpiderOutput();
    void checkAvailability();
    void verifyAvailability(int exitCode);
    void showQRCode();

private:
    Ui::MainWidget *ui;
    ShadowsocksServerListModel *model_;
    QSystemTrayIcon *tray_;
    QProcess *spider_;
    QTimer *retryTimer_;
    QTimer *checkTimer_;
    QProcess *checker_;
};


#endif // MAINWIDGET_H
