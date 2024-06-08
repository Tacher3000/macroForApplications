#ifndef CREATEMACRODIALOG_H
#define CREATEMACRODIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFont>
#include <QDir>
#include <QDebug>
#include <QComboBox>
#include <QVector>
#include <memory>
#include "keylineedit.h"
#include "programmanager.h"

#ifdef _WIN32
#include "windowsprogrammanager.h"
#elif __linux__
// #include "linuxprogrammanager.h"
#endif


class CreateMacroDialog : public QDialog
{
    Q_OBJECT
public:
    CreateMacroDialog(QWidget *parent = nullptr);
private slots:
    void chooseFile();
//    void saveDataToVector();
    void saveDataToJsonFile();

private:
//    QJsonArray *data;

    QGridLayout *mainLayout;

    KeyLineEdit *keyboardShortcut;

    QLineEdit *titleLineEdit;

    QComboBox *applications;

    QLineEdit *fileWayEdit;
    QPushButton *fileSelectionButton;

    QPushButton *addButton;

    std::unique_ptr<ProgramManager> _programManager;

};

#endif // CREATEMACRODIALOG_H
