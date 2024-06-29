#include "CentralWindow.h"

CentralWindow::CentralWindow(QWidget *parent)
    : QWidget(parent),
    jsonArrayManipulations(new JsonArrayManipulations("config/configure.json"))
{
    manager = new ShortcutManager(this);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setDirection(QBoxLayout::BottomToTop);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    mainLayout->addStretch();

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
    // manager->addShortcut("Ctrl+Alt+T", "notepad");
    for (const QJsonValue &value : entries)
    {
        if (value.isObject())
        {
            QJsonObject entryObj = value.toObject();
            // Извлечение данных из JSON-объекта
            QString iconPath = entryObj.value("iconPath").toString();
            QString keyboardShortcut = entryObj.value("keyboardShortcut").toString();
            QString programName = entryObj.value("programName").toString();
            QString title = entryObj.value("title").toString();
            QString programPath = entryObj.value("installPath").toString();

            // Добавление элемента в макет
            addEntryToLayout(entryObj);

            // Добавление сочетания клавиш в менеджер
            manager->addShortcut(keyboardShortcut, programPath);
        }
    }
}

void CentralWindow::addEntryToLayout(const QJsonObject &entry)
{
    EntryWidget *entryWidget = new EntryWidget(entry, this);
    mainLayout->addWidget(entryWidget);
}

void CentralWindow::addEntryToManager(const QJsonObject &entry)
{
    EntryWidget *entryWidget = new EntryWidget(entry, this);
}
