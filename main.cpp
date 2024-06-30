#include "src/mainwindow.h"
#include "src/windowsglobalhotkeymanager.h"

#include <QApplication>

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include <QTranslator>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    // WindowsGlobalHotkeyManager hotkeyManager;
    // hotkeyManager.registerHotkey("Control+Alt+S", 1);
    // hotkeyManager.registerHotkey("1+2+3", 2);
    // hotkeyManager.registerHotkey("Z+X+C", 3);

    // QObject::connect(&hotkeyManager, &WindowsGlobalHotkeyManager::hotkeyPressed, [](const QString &hotkey) {
    //     QMessageBox::information(nullptr, "Hotkey Pressed", "Hotkey pressed: " + hotkey);
    // });

    // hotkeyManager.show();
    // QTranslator translator;
    // if (translator.load(":/translations/ru_RU.qm")) {
    //     a.installTranslator(&translator);
    // } else {
    //     qDebug() << "Failed to load translation file.";
    // }

    return a.exec();
}
