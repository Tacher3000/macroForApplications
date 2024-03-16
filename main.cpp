#include "mainwindow.h"

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


    QJsonObject recordObject;

    QJsonObject objObject;
    objObject.insert("Test1", "1");
    objObject.insert("Test2", "2");
    objObject.insert("Test3", "3");

    QJsonObject obj2Object;
    obj2Object.insert("Test4", "4");
    obj2Object.insert("Test5", "5");
    obj2Object.insert("Test6", "6");
    obj2Object.insert("Test7", QJsonValue::fromVariant("1"));
    obj2Object.insert("Test8", QJsonValue::fromVariant(123.4));
    obj2Object.insert("Test9", QJsonValue::fromVariant(43));
    obj2Object.insert("Test10", QJsonValue::fromVariant(true));


    objObject.insert("Test11", obj2Object);
    recordObject.insert("Test12",objObject);



    QJsonDocument doc(recordObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    qDebug() << QCoreApplication::applicationDirPath();
    QFile file;
    file.setFileName("test.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream( &file );
    stream << jsonString;
    file.close();




    return a.exec();
}
