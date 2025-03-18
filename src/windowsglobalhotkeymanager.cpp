#include "windowsglobalhotkeymanager.h"
#include <QApplication>
#include <QDebug>

WindowsGlobalHotkeyManager::WindowsGlobalHotkeyManager(QWidget* parent)
    : QWidget(parent), nextId(1)
{
    qDebug() << "Installing native event filter for WindowsGlobalHotkeyManager";
    QApplication::instance()->installNativeEventFilter(this);
}

WindowsGlobalHotkeyManager::~WindowsGlobalHotkeyManager()
{
    qDebug() << "Unregistering all hotkeys and removing event filter";
    for(const int id : hotkeyMap.keys()) {
        UnregisterHotKey(NULL, id);
    }
    QApplication::instance()->removeNativeEventFilter(this);
}

bool WindowsGlobalHotkeyManager::registerHotkey(Qt::Key key, Qt::KeyboardModifiers modifiers)
{
    UINT winKey = convertQtKeyToWindows(key);
    UINT winModifiers = convertQtModifiersToWindows(modifiers);

    qDebug() << "Registering hotkey - Key:" << key << ", Modifiers:" << modifiers;
    qDebug() << "Converted to Windows - Key:" << winKey << ", Modifiers:" << winModifiers;

    if (winKey == 0) {
        qDebug() << "Failed to convert Qt key to Windows key";
        return false;
    }

    int id = nextId++;
    if (RegisterHotKey(NULL, id, winModifiers | MOD_NOREPEAT, winKey)) {
        hotkeyMap[id] = qMakePair(key, modifiers);
        qDebug() << "Hotkey registered with ID:" << id;
        return true;
    } else {
        qDebug() << "Failed to register hotkey with Windows API. Error:" << GetLastError();
        return false;
    }
}

bool WindowsGlobalHotkeyManager::unregisterHotkey(Qt::Key key, Qt::KeyboardModifiers modifiers)
{
    for (auto it = hotkeyMap.begin(); it != hotkeyMap.end(); ++it) {
        if (it.value().first == key && it.value().second == modifiers) {
            bool result = UnregisterHotKey(NULL, it.key());
            if (result) {
                hotkeyMap.erase(it);
                qDebug() << "Hotkey unregistered successfully";
                return true;
            }
            qDebug() << "Failed to unregister hotkey. Error:" << GetLastError();
            return false;
        }
    }
    qDebug() << "Hotkey not found for unregistering";
    return false;
}

bool WindowsGlobalHotkeyManager::nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result)
{
    qDebug() << "Received event type:" << eventType;
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        qDebug() << "Message received:" << msg->message;
        if (msg->message == WM_HOTKEY) {
            int id = static_cast<int>(msg->wParam);
            qDebug() << "WM_HOTKEY received with ID:" << id;
            if (hotkeyMap.contains(id)) {
                auto hotkey = hotkeyMap[id];
                qDebug() << "Emitting hotkeyPressed for Key:" << hotkey.first << ", Modifiers:" << hotkey.second;
                emit hotkeyPressed(hotkey.first, hotkey.second);
                if (result) *result = 1;
                return true;
            } else {
                qDebug() << "Hotkey ID not found in map:" << id;
            }
        }
    }
    return false;
}

UINT WindowsGlobalHotkeyManager::convertQtKeyToWindows(Qt::Key key)
{
    qDebug() << "Converting Qt key:" << key;
    if (key >= Qt::Key_A && key <= Qt::Key_Z) {
        return static_cast<UINT>(key);
    }
    if (key >= Qt::Key_0 && key <= Qt::Key_9) {
        return static_cast<UINT>(key);
    }

    switch (key) {
    case Qt::Key_Space: return VK_SPACE;
    case Qt::Key_Return: return VK_RETURN;
    case Qt::Key_Enter: return VK_RETURN;
    case Qt::Key_Escape: return VK_ESCAPE;
    case Qt::Key_F1: return VK_F1;
    case Qt::Key_F2: return VK_F2;
    default:
        qDebug() << "Unsupported key, returning 0";
        return 0;
    }
}

UINT WindowsGlobalHotkeyManager::convertQtModifiersToWindows(Qt::KeyboardModifiers modifiers)
{
    qDebug() << "Converting modifiers:" << modifiers;
    UINT winModifiers = 0;
    if (modifiers & Qt::ShiftModifier) winModifiers |= MOD_SHIFT;
    if (modifiers & Qt::ControlModifier) winModifiers |= MOD_CONTROL;
    if (modifiers & Qt::AltModifier) winModifiers |= MOD_ALT;
    if (modifiers & Qt::MetaModifier) winModifiers |= MOD_WIN;
    qDebug() << "Converted modifiers to Windows:" << winModifiers;
    return winModifiers;
}
