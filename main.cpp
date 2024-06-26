#include "src/mainwindow.h"

#include <QApplication>

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();


    return a.exec();
}
