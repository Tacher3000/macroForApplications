#include <QApplication>
#include "src/mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile file("debug_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString() << " - "
            << (type == QtDebugMsg ? "DEBUG" : "OTHER") << ": "
            << msg << "\n";
        file.close();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageHandler);
    QApplication app(argc, argv);

    // WindowsGlobalHotkeyManager* hotkeyManager = new WindowsGlobalHotkeyManager();
    // ShortcutManager* shortcutManager = new ShortcutManager(hotkeyManager);

    // shortcutManager->registerShortcut("Ctrl+Shift+Q", "C:/Windows/notepad.exe");

    MainWindow window;
    window.show();

    return app.exec();
}
