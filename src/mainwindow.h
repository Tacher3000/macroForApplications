#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QStackedWidget>
#include "navigator.h"
#include "screensfactory.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void showWindow();
    void hideWindow();

private:
    QStackedWidget *stackedWidget;
    Navigator *navigator;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
};

#endif // MAINWINDOW_H
