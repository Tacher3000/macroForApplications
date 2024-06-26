#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "centralwindow.h"

#include <QShortcut>
#include <QApplication>
#include <QKeySequence>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void test();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QStackedWidget *stackedWidget;

    QSystemTrayIcon *trayIcon;
};
#endif // MAINWINDOW_H
