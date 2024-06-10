#include "CentralWindow.h"

CentralWindow::CentralWindow(QWidget *parent)
    : QWidget(parent),
    jsonArrayManipulations(new JsonArrayManipulations("config/configure.json"))
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

    addMacroButton = new QPushButton(this);
    addMacroButton->setText("+");
    addMacroButton->setMinimumSize(500, 50);
    addMacroButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addMacroButton->setMaximumSize(800, 50);
    mainLayout->addWidget(addMacroButton);

    macroDialog = new CreateMacroDialog(this);
    QObject::connect(addMacroButton, &QPushButton::clicked, macroDialog, &CreateMacroDialog::exec);

    loadEntries();
    setLayout(mainLayout);
}

void CentralWindow::loadEntries()
{
    QJsonArray entries = jsonArrayManipulations->getEntries();
    for (const QJsonValue &value : entries)
    {
        if (value.isObject())
        {
            addEntryToLayout(value.toObject());
        }
    }
}

void CentralWindow::addEntryToLayout(const QJsonObject &entry)
{
    EntryWidget *entryWidget = new EntryWidget(entry, this);
    mainLayout->addWidget(entryWidget);
}
