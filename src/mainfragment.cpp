// mainfragment.cpp
#include "mainfragment.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "screens.h"

MainFragment::MainFragment(QWidget *parent)
    : BaseFragment(parent)
{
}

void MainFragment::init()
{
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
    connect(addMacroButton, &QPushButton::clicked, this, [this]() {
        emit navigateTo(screens::ADD_COMBINATION_TAG);
    });

    hotkeyManager = new WindowsGlobalHotkeyManager(this);
    shortcutManager = new ShortcutManager(hotkeyManager, this);
    jsonArrayManipulations = new JsonArrayManipulations("config/configure.json");

    loadEntries();

    QPushButton *settingsButton = new QPushButton("Настройки", this);
    mainLayout->addWidget(settingsButton);
    connect(settingsButton, &QPushButton::clicked, this, [this]() {
        emit navigateTo(screens::SETTINGS_TAG);
    });

    connect(this, &MainFragment::macroCreated, this, [this](const QJsonObject &entry) {
        addEntryToLayout(entry);
        addEntryToManager(entry);
        jsonArrayManipulations->addEntry(entry);
    });

    setLayout(mainLayout);
}

void MainFragment::loadEntries()
{
    qDebug() << "Loading entries from JSON...";
    QJsonArray entries = jsonArrayManipulations->getEntries();
    qDebug() << "Found" << entries.size() << "entries.";
    for (const QJsonValue &value : entries)
    {
        if (value.isObject())
        {
            QJsonObject entryObj = value.toObject();
            qDebug() << "Processing entry:" << entryObj;
            addEntryToLayout(entryObj);
            addEntryToManager(entryObj);
        }
    }
}

void MainFragment::addEntryToLayout(const QJsonObject &entry)
{
    EntryWidget *entryWidget = new EntryWidget(entry, this);
    mainLayout->addWidget(entryWidget);
    qDebug() << "Added entry to layout:" << entry;
}

void MainFragment::addEntryToManager(const QJsonObject &entry)
{
    QString keyboardShortcut = entry.value("keyboardShortcut").toString();
    QString programPath = entry.value("installPath").toString();
    QString filePath = entry.value("filePath").toString();

    qDebug() << "Attempting to register shortcut:" << keyboardShortcut;
    qDebug() << "Program path:" << programPath << ", File path:" << filePath;

    if (!keyboardShortcut.isEmpty()) {
        if (!filePath.isEmpty()) {
            qDebug() << "Registering file path:" << filePath;
            shortcutManager->registerShortcut(keyboardShortcut, filePath);
        } else if (!programPath.isEmpty()) {
            qDebug() << "Registering program path:" << programPath;
            shortcutManager->registerShortcut(keyboardShortcut, programPath);
        } else {
            qDebug() << "No valid path found for shortcut:" << keyboardShortcut;
        }
    } else {
        qDebug() << "Invalid keyboard shortcut:" << keyboardShortcut;
    }
}
