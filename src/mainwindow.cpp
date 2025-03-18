#include "mainwindow.h"
#include <QAction>
#include <QCloseEvent>
#include <QDebug>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    ScreensFactory *factory = new ScreensFactory(this);
    navigator = new Navigator(stackedWidget, factory, this);

    setWindowTitle("Macro for Applications");
    resize(800, 600);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/trayIcon.png"));
    trayIcon->setToolTip("Macro for Applications");
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);

    trayMenu = new QMenu(this);
    QAction *showAction = new QAction("Показать", this);
    QAction *hideAction = new QAction("Скрыть", this);
    QAction *quitAction = new QAction("Выход", this);

    connect(showAction, &QAction::triggered, this, &MainWindow::showWindow);
    connect(hideAction, &QAction::triggered, this, &MainWindow::hideWindow);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    trayMenu->addAction(showAction);
    trayMenu->addAction(hideAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
        trayIcon->showMessage("Macro for Applications",
                              "Приложение свёрнуто в трей. Используйте контекстное меню для управления.",
                              QSystemTrayIcon::Information,
                              3000);
    } else {
        event->accept();
    }
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if (isVisible()) {
            hideWindow();
        } else {
            showWindow();
        }
        break;
    default:
        break;
    }
}

void MainWindow::showWindow()
{
    show();
    setWindowState(Qt::WindowActive);
    raise();
    activateWindow();
}

void MainWindow::hideWindow()
{
    hide();
}
