#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    CentralWindow *mCentralWindow = new CentralWindow(this);

    stackedWidget->addWidget(mCentralWindow);
    setCentralWidget(stackedWidget);

    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+O"),
                                        this);
    QObject::connect(shortcut, &QShortcut::activated, this, &MainWindow::test);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/trayIcon.png"));

    // Создание контекстного меню для значка в трее
    QMenu *menu = new QMenu(this);
    QAction *restoreAction = new QAction("Показать", this);
    QAction *quitAction = new QAction("Выйти", this);
    menu->addAction(restoreAction);
    menu->addAction(quitAction);

    connect(restoreAction, &QAction::triggered, this, &MainWindow::show);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    trayIcon->setContextMenu(menu);

    // Отображение значка в трее
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
    if (trayIcon->isVisible()) {
        hide(); // Скрыть главное окно
        event->ignore(); // Игнорировать событие закрытия
    }
}

