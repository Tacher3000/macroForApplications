#ifndef WINDOWSGLOBALHOTKEYMANAGER_H
#define WINDOWSGLOBALHOTKEYMANAGER_H

#include "globalhotkeymanager.h"
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QMap>
#include <QSet>
#include <windows.h>



class WindowsGlobalHotkeyManager : public QWidget, public GlobalHotkeyManager
{
    Q_OBJECT
public:
    WindowsGlobalHotkeyManager(QWidget *parent = nullptr) : QWidget(parent) {}

    ~WindowsGlobalHotkeyManager();

    bool registerHotkey(const QString &hotkey, int id);

signals:
    void hotkeyPressed(const QString &hotkey);

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;

private:
    QMap<int, QString> _registeredHotkeys;

    QSet<Qt::Key> parseHotkey(const QString &hotkey);
};

#endif // WINDOWSGLOBALHOTKEYMANAGER_H
