#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    CentralWindow *mCentralWindow = new CentralWindow(this);

    stackedWidget->addWidget(mCentralWindow);
    setCentralWidget(stackedWidget);

    // QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+O"),
    //                                     this);
    // QObject::connect(shortcut, &QShortcut::activated, this, &MainWindow::test);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/trayIcon.png"));

    QMenu *menu = new QMenu(this);
    QAction *restoreAction = new QAction(tr("Show"), this);
    QAction *quitAction = new QAction(tr("Quit"), this);
    menu->addAction(restoreAction);
    menu->addAction(quitAction);

    connect(restoreAction, &QAction::triggered, this, &MainWindow::show);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    trayIcon->setContextMenu(menu);

    trayIcon->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::test()
{
    qDebug() << "xyi";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // расскоментировать

    // if (trayIcon->isVisible()) {
    //     hide();
    //     event->ignore();
    // }
}

