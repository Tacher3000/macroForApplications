#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H

#include <QObject>
#include <QMap>
#include <QKeySequence>
#include <QShortcut>
#include <QString>
#include <QProcess>
#include <QDebug>

class ShortcutManager : public QObject
{
    Q_OBJECT

public:
    explicit ShortcutManager(QObject *parent = nullptr);

    // Метод для добавления комбинации клавиш и связанного с ней приложения
    void addShortcut(const QString &keySequence, const QString &applicationPath);

private slots:
    // Слот для запуска приложения по сочетанию клавиш
    void launchApplication();

private:
    QMap<QShortcut *, QString> shortcuts;
};


#endif // SHORTCUTMANAGER_H
