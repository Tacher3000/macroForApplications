#include "src/mainwindow.h"

#include <QApplication>

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include "src/shortcutmanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    ShortcutManager manager(&w);
    manager.addShortcut("Ctrl+Alt+T", "notepad");
    // ListInstalledPrograms();

    return a.exec();
}
