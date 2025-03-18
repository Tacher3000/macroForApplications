// shortcutmanager.cpp
#include "shortcutmanager.h"
#include <QProcess>
#include <QDebug>
#include <QKeySequence>

ShortcutManager::ShortcutManager(WindowsGlobalHotkeyManager* manager, QObject* parent)
    : QObject(parent), hotkeyManager(manager)
{
    connect(hotkeyManager, &WindowsGlobalHotkeyManager::hotkeyPressed,
            this, &ShortcutManager::onHotkeyPressed);
}

bool ShortcutManager::registerShortcut(const QString& keySequence, const QString& appPath)
{
    QKeySequence ks(keySequence);
    if (ks.isEmpty()) {
        qDebug() << "Invalid key sequence:" << keySequence;
        return false;
    }

    // Парсим модификаторы и базовую клавишу
    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    Qt::Key key = Qt::Key_unknown;

    // Разбиваем строку на части
    QStringList parts = keySequence.split("+", Qt::SkipEmptyParts);
    if (parts.isEmpty()) {
        qDebug() << "No valid parts in key sequence:" << keySequence;
        return false;
    }

    // Проходим по всем частям для извлечения модификаторов
    for (const QString& part : parts) {
        QString trimmedPart = part.trimmed().toLower();
        if (trimmedPart == "ctrl") {
            modifiers |= Qt::ControlModifier;
        } else if (trimmedPart == "shift") {
            modifiers |= Qt::ShiftModifier;
        } else if (trimmedPart == "alt") {
            modifiers |= Qt::AltModifier;
        } else if (trimmedPart == "meta") {
            modifiers |= Qt::MetaModifier;
        } else {
            // Последняя часть считается базовой клавишей
            key = static_cast<Qt::Key>(QKeySequence(trimmedPart)[0] & ~Qt::KeyboardModifierMask);
        }
    }

    if (key == Qt::Key_unknown) {
        qDebug() << "No valid key found in sequence:" << keySequence;
        return false;
    }

    qDebug() << "Attempting to register shortcut:" << keySequence << "for app:" << appPath;
    qDebug() << "Parsed Key:" << key << ", Modifiers:" << modifiers;

    if (hotkeyManager && hotkeyManager->registerHotkey(key, modifiers)) {
        shortcutToAppMap[qMakePair(key, modifiers)] = appPath;
        qDebug() << "Shortcut registered successfully:" << keySequence << "-> " << appPath;
        return true;
    }
    qDebug() << "Failed to register shortcut:" << keySequence << "Error code:" << GetLastError();
    return false;
}

void ShortcutManager::onHotkeyPressed(Qt::Key key, Qt::KeyboardModifiers modifiers)
{
    QPair<Qt::Key, Qt::KeyboardModifiers> keyPair = qMakePair(key, modifiers);
    qDebug() << "Hotkey pressed:" << key << "+" << modifiers << "Looking for mapping...";
    if (shortcutToAppMap.contains(keyPair)) {
        QString appPath = shortcutToAppMap[keyPair];
        qDebug() << "Launching:" << appPath;

        QProcess* process = new QProcess(this);
        bool started = process->startDetached(appPath);

        if (started) {
            qDebug() << "Successfully launched:" << appPath;
        } else {
            qDebug() << "Failed to launch:" << appPath << "Error:" << process->errorString();
        }

        process->deleteLater();
    } else {
        qDebug() << "No mapping found for:" << key << "+" << modifiers;
    }
}
