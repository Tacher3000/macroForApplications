#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
//    QVBoxLayout *layout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget(this);
    CentralWindow *mCentralWindow = new CentralWindow(this);

    stackedWidget->addWidget(mCentralWindow);
//    layout->addWidget(mCentralWindow);
    setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow()
{
}

