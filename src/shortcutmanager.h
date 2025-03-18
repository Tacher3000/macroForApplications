#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H

#include <QObject>
#include <QKeySequence>
#include "windowsglobalhotkeymanager.h"

class ShortcutManager : public QObject
{
    Q_OBJECT
public:
    explicit ShortcutManager(WindowsGlobalHotkeyManager* manager, QObject* parent = nullptr);
    bool registerShortcut(const QString& keySequence, const QString& appPath);

private slots:
    void onHotkeyPressed(Qt::Key key, Qt::KeyboardModifiers modifiers);

private:
    WindowsGlobalHotkeyManager* hotkeyManager;
    QMap<QPair<Qt::Key, Qt::KeyboardModifiers>, QString> shortcutToAppMap;
};

#endif
