#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    main_layout = new QVBoxLayout(ui->centralwidget);
    main_layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    test = new QPushButton(this);
    test->setText("+");
    test->setMinimumSize(100, 50);
    test->setMaximumSize(800, 50);
    test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    test2 = new CreateMacroDialog(this);
    QObject::connect(test, &QPushButton::clicked, test2, &CreateMacroDialog::exec);

    main_layout->addWidget(test);
    ui->centralwidget->setLayout(main_layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

