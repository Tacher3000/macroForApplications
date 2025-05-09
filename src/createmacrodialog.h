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
#include <QJsonArray>
#include <QVector>
#include <memory>
#include "keylineedit.h"
#include "programmanager.h"
#include "jsonarraymanipulations.h"

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
    void fillComboBoxWithPrograms(const QMap<QString, QString>& programMap);

private slots:
    void chooseFile();

    void saveDataToJsonFile();

private:
    QGridLayout *mainLayout;

    KeyLineEdit *keyboardShortcut;

    QLineEdit *titleLineEdit;

    QComboBox *applications;

    QLineEdit *fileWayEdit;
    QPushButton *fileSelectionButton;

    QPushButton *addButton;

    std::unique_ptr<ProgramManager> _programManager;

signals:
    void macroCreated(const QJsonObject &entry);
};

#endif // CREATEMACRODIALOG_H
