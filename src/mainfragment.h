#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include "basefragment.h"
#include "shortcutmanager.h"
#include "windowsglobalhotkeymanager.h"
#include "createmacrodialog.h"
#include "jsonarraymanipulations.h"
#include "entrywidget.h"

#include <QListWidget>

class MainFragment : public BaseFragment
{
    Q_OBJECT
public:
    explicit MainFragment(QWidget *parent = nullptr);
    void init() override;

private:
    QVBoxLayout *mainLayout;
    QPushButton *addMacroButton;
    CreateMacroDialog *macroDialog;
    ShortcutManager *shortcutManager;
    WindowsGlobalHotkeyManager *hotkeyManager;
    JsonArrayManipulations *jsonArrayManipulations;

    void loadEntries();

    void addEntryToLayout(const QJsonObject &entry);

    void addEntryToManager(const QJsonObject &entry);

    QListWidget *combinationsList;
signals:
    void macroCreated(const QJsonObject &entry);
};

#endif // MAINFRAGMENT_H
