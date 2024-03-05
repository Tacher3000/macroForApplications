#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    opener = new KeyAppOpener;
    ui->centralwidget->setLayout(opener->getLayout());
}

MainWindow::~MainWindow()
{
    delete ui;
}

