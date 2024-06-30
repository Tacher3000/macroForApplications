#include "shortcutmanager.h"

ShortcutManager::ShortcutManager(QObject *parent, WindowsGlobalHotkeyManager *hotkeyManager)
    : QObject(parent), hotkeyManager(hotkeyManager) {
    if (hotkeyManager) {
        connect(hotkeyManager, &WindowsGlobalHotkeyManager::hotkeyPressed, this, &ShortcutManager::launchApplication);
    } else {
        qDebug() << "hotkeyManager is null";
    }
}

void ShortcutManager::addShortcut(const QString &keySequence, const QString &applicationPath) {
    static int hotkeyId = 1; // ID для регистрации горячих клавиш
    if (hotkeyManager && hotkeyManager->registerHotkey(keySequence, hotkeyId)) {
        shortcuts.insert(keySequence, applicationPath);
        qDebug() << "Ярлык" << keySequence << "подключен к приложению" << applicationPath;
        hotkeyId++;
    } else {
        qDebug() << "Не удалось подключить ярлык" << keySequence;
    }
}

void ShortcutManager::launchApplication(const QString &keySequence) {
    if (shortcuts.contains(keySequence)) {
        QString applicationPath = shortcuts.value(keySequence);
        qDebug() << "Попытка запуска приложения:" << applicationPath;
        bool started = QProcess::startDetached(applicationPath);
        if (started) {
            qDebug() << "Приложение успешно запущено:" << applicationPath;
        } else {
            qDebug() << "Не удалось запустить приложение:" << applicationPath;
        }
    } else {
        qDebug() << "Ярлык не найден или отправитель недействителен.";
    }
}
