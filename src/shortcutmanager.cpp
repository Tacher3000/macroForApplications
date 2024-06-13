#include "shortcutmanager.h"

ShortcutManager::ShortcutManager(QObject *parent) : QObject(parent) {}

void ShortcutManager::addShortcut(const QString &keySequence, const QString &applicationPath) {
    QKeySequence shortcut(keySequence);
    if (!shortcut.isEmpty()) {
        QShortcut *sc = new QShortcut(shortcut, this);
        shortcuts.insert(sc, applicationPath);
        bool connected = connect(sc, &QShortcut::activated, this, &ShortcutManager::launchApplication);
        if (connected) {
            qDebug() << "Ярлык" << keySequence << "подключен к приложению" << applicationPath;
        } else {
            qDebug() << "Не удалось подключить ярлык" << keySequence;
        }
    } else {
        qDebug() << "Недопустимая последовательность клавиш:" << keySequence;
    }
}

// void ShortcutManager::launchApplication() {
//     QShortcut *shortcut = qobject_cast<QShortcut *>(sender());
//     if (shortcut && shortcuts.contains(shortcut)) {
//         QString applicationPath = shortcuts.value(shortcut);
//         QProcess::startDetached(applicationPath);
//         qDebug() << "sisi pisi";
//     }
// }
void ShortcutManager::launchApplication() {
    // Преобразование отправителя сигнала в QShortcut
    QShortcut *shortcut = qobject_cast<QShortcut *>(sender());

    // Проверка, что отправитель является QShortcut и содержится в словаре shortcuts
    if (shortcut && shortcuts.contains(shortcut)) {
        // Получение имени приложения, связанного с ярлыком
        QString applicationName = shortcuts.value(shortcut);
        qDebug() << "Попытка запуска приложения:" << applicationName;

        // Запуск приложения с помощью QProcess::startDetached
        bool started = QProcess::startDetached(applicationName);

        // Проверка успешности запуска приложения
        if (started) {
            qDebug() << "Приложение успешно запущено:" << applicationName;
        } else {
            qDebug() << "Не удалось запустить приложение:" << applicationName;
        }
    } else {
        qDebug() << "Ярлык не найден или отправитель недействителен.";
    }
}

