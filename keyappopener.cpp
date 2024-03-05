#include "keyappopener.h"
#include <QFileDialog>


KeyAppOpener::KeyAppOpener()
{
    testLine = new HotKeyLineEdit();
    testLine->setMinimumSize(400, 50);
    testLine->setMaximumSize(500, 50);

    pathLine = new QLineEdit();
    pathLine->setMinimumSize(400, 50);
    pathLine->setMaximumSize(500, 50);

    pathButton = new QPushButton();
    pathButton->setMinimumSize(100, 50);
    pathButton->setMaximumSize(150, 50);
    QObject::connect(pathButton, &QPushButton::clicked, this, [=]() {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.*)");
        if (!fileName.isEmpty()) {
            pathLine->setText(fileName);
        }
    });

    mainLayout = new QGridLayout();
    mainLayout->addWidget(testLine, 0, 0, 1, 1);
    mainLayout->addWidget(pathLine, 0, 1, 1, 1);
    mainLayout->addWidget(pathButton, 0, 3, 1, 1);
}

QGridLayout *KeyAppOpener::getLayout()
{
    return mainLayout;
}

