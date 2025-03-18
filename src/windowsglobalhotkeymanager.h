#ifndef WINDOWSGLOBALHOTKEYMANAGER_H
#define WINDOWSGLOBALHOTKEYMANAGER_H

#include <QWidget>
#include <QAbstractNativeEventFilter>
#include <Windows.h>
#include "globalhotkeymanager.h"

class WindowsGlobalHotkeyManager : public QWidget, public GlobalHotkeyManager, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    WindowsGlobalHotkeyManager(QWidget* parent = nullptr);
    ~WindowsGlobalHotkeyManager();

    bool registerHotkey(Qt::Key key, Qt::KeyboardModifiers modifiers);
    bool unregisterHotkey(Qt::Key key, Qt::KeyboardModifiers modifiers);

signals:
    void hotkeyPressed(Qt::Key key, Qt::KeyboardModifiers modifiers);

protected:
    bool nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result) override;

private:
    QMap<int, QPair<Qt::Key, Qt::KeyboardModifiers>> hotkeyMap;
    int nextId;

    UINT convertQtKeyToWindows(Qt::Key key);
    UINT convertQtModifiersToWindows(Qt::KeyboardModifiers modifiers);
};

#endif // WINDOWSGLOBALHOTKEYMANAGER_H
