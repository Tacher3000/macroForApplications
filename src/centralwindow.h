#ifndef CENTRALWINDOW_H
#define CENTRALWINDOW_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "createmacrodialog.h"
#include "JsonArrayManipulations.h"
#include "EntryWidget.h"
#include "shortcutmanager.h"


class CentralWindow : public QWidget
{
    Q_OBJECT
public:
    CentralWindow(QWidget *parent = nullptr);
private:
    QVBoxLayout *mainLayout;
    QPushButton *addMacroButton;
    CreateMacroDialog *macroDialog;
    ShortcutManager *manager;

    JsonArrayManipulations *jsonArrayManipulations;

    void loadEntries();
    void addEntryToLayout(const QJsonObject &entry);
    void addEntryToManager(const QJsonObject &entry);
};

#endif // CENTRALWINDOW_H
