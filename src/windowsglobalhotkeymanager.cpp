#include "windowsglobalhotkeymanager.h"
#include <QDebug>

// Деструктор: снимает регистрацию всех зарегистрированных горячих клавиш
WindowsGlobalHotkeyManager::~WindowsGlobalHotkeyManager() {
    qDebug() << "Деструктор: снимаем регистрацию всех горячих клавиш";
    for (int id : _registeredHotkeys.keys()) {
        UnregisterHotKey((HWND)winId(), id);
        qDebug() << "Снята регистрация горячей клавиши с id:" << id;
    }
}

// Регистрация горячей клавиши с заданным идентификатором
bool WindowsGlobalHotkeyManager::registerHotkey(const QString &hotkey, int id) {
    qDebug() << "Попытка зарегистрировать горячую клавишу:" << hotkey << "с id:" << id;
    QSet<Qt::Key> keys = parseHotkey(hotkey);
    if (keys.isEmpty()) {
        qDebug() << "Ошибка: Неверная строка горячей клавиши";
        return false;
    }

    UINT fsModifiers = 0;
    UINT vk = 0;
    bool hasNonModifierKey = false;
    for (Qt::Key key : keys) {
        if (key == Qt::Key_Control)
            fsModifiers |= MOD_CONTROL;
        else if (key == Qt::Key_Alt)
            fsModifiers |= MOD_ALT;
        else if (key == Qt::Key_Shift)
            fsModifiers |= MOD_SHIFT;
        else if (key == Qt::Key_Meta)
            fsModifiers |= MOD_WIN;
        else {
            vk = key;
            hasNonModifierKey = true;
        }
    }

    if (!hasNonModifierKey) {
        qDebug() << "Ошибка: Не установлены основная клавиша";
        return false;
    }

    if (RegisterHotKey((HWND)winId(), id, fsModifiers, vk)) {
        _registeredHotkeys[id] = hotkey;
        qDebug() << "Успешно зарегистрирована горячая клавиша:" << hotkey << "с id:" << id;
        return true;
    }
    qDebug() << "Ошибка: Не удалось зарегистрировать горячую клавишу";
    return false;
}

// Обработчик нативных событий для обработки сообщений горячих клавиш
bool WindowsGlobalHotkeyManager::nativeEvent(const QByteArray &eventType, void *message, qintptr *result) {
    if (eventType == "windows_generic_MSG") {
        MSG *msg = static_cast<MSG *>(message);
        if (msg->message == WM_HOTKEY) {
            int id = msg->wParam;
            if (_registeredHotkeys.contains(id)) {
                qDebug() << "Получено сообщение о нажатии горячей клавиши с id:" << id;

                QString hotkey = _registeredHotkeys[id];
                QSet<Qt::Key> keys = parseHotkey(hotkey);

                bool allKeysPressed = true;

                for (Qt::Key key : keys) {
                    int virtualKey = 0;
                    switch (key) {
                    case Qt::Key_Control:
                        virtualKey = VK_CONTROL;
                        break;
                    case Qt::Key_Alt:
                        virtualKey = VK_MENU;
                        break;
                    case Qt::Key_Shift:
                        virtualKey = VK_SHIFT;
                        break;
                    case Qt::Key_Meta:
                        virtualKey = VK_LWIN; // Левый Win
                        break;
                    default:
                        virtualKey = key;
                        break;
                    }

                    // Если хотя бы одна клавиша не нажата, флаг allKeysPressed становится false
                    if (!(GetAsyncKeyState(virtualKey) & 0x8000)) {
                        allKeysPressed = false;
                        break;
                    }
                }

                if (allKeysPressed) {
                    emit hotkeyPressed(hotkey);
                    return true;
                } else {
                    qDebug() << "Не все клавиши из сочетания были нажаты";
                }
            }
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}


// Парсинг строки горячей клавиши и преобразование ее в набор значений Qt::Key
QSet<Qt::Key> WindowsGlobalHotkeyManager::parseHotkey(const QString &hotkey) {
    QSet<Qt::Key> keys;
    QStringList parts = hotkey.split('+');
    qDebug() << "Парсинг горячей клавиши:" << hotkey;
    for (const QString &part : parts) {
        if (part == "Control")
            keys.insert(Qt::Key_Control);
        else if (part == "Alt")
            keys.insert(Qt::Key_Alt);
        else if (part == "Shift")
            keys.insert(Qt::Key_Shift);
        else if (part == "Meta")
            keys.insert(Qt::Key_Meta);
        else if (part.size() == 1)
            keys.insert(Qt::Key(part.at(0).unicode()));
        else {
            qDebug() << "Ошибка: Неверная часть горячей клавиши:" << part;
            return QSet<Qt::Key>();
        }
    }
    qDebug() << "Успешно распарсены клавиши:" << keys;
    return keys;
}
