#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QProcess>
#include "windowsglobalhotkeymanager.h" // Add this line

class ShortcutManager : public QObject {
    Q_OBJECT
public:
    explicit ShortcutManager(QObject *parent = nullptr, WindowsGlobalHotkeyManager *hotkeyManager = nullptr);
    void addShortcut(const QString &keySequence, const QString &applicationPath);

private slots:
    void launchApplication(const QString &keySequence);

private:
    QMap<QString, QString> shortcuts;
    WindowsGlobalHotkeyManager *hotkeyManager; // Add this line
};

#endif // SHORTCUTMANAGER_H
