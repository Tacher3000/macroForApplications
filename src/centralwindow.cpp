#include "centralwindow.h"

CentralWindow::CentralWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    main_layout->setSizeConstraint(QLayout::SetMinimumSize);

    test = new QPushButton(this);
    test->setText("+");
    test->setMinimumSize(500, 50);
    test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    test->setMaximumSize(800, 50);
    main_layout->addWidget(test);
//    test->setFixedSize(100, 50);
//    test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    test->setStyleSheet("QPushButton { margin: 0 auto; }");
//    test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    test2 = new CreateMacroDialog(this);
    QObject::connect(test, &QPushButton::clicked, test2, &CreateMacroDialog::exec);
    setLayout(main_layout);
}
