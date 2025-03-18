#ifndef ADDCOMBINATIONFRAGMENT_H
#define ADDCOMBINATIONFRAGMENT_H

#include "basefragment.h"
#include <QComboBox>
#include <QGridLayout>
#include <QJsonObject>
#include <QPushButton>
#include "keylineedit.h"
#include "programmanager.h"
#include "jsonarraymanipulations.h"

#ifdef _WIN32
#include "windowsprogrammanager.h"
#elif __linux__
// #include "linuxprogrammanager.h"
#endif

class AddCombinationFragment : public BaseFragment
{
    Q_OBJECT
public:
    explicit AddCombinationFragment(QWidget *parent = nullptr);
    void init() override;

private slots:
    void chooseFile();
    void saveCombination();

private:
    QGridLayout *mainLayout;
    KeyLineEdit *keyboardShortcut;
    QLineEdit *titleLineEdit;
    QComboBox *applications;
    QLineEdit *filePathEdit;
    QPushButton *fileSelectionButton;
    QPushButton *saveButton;

    std::unique_ptr<ProgramManager> programManager;
    JsonArrayManipulations *jsonManipulator;

    void fillComboBoxWithPrograms(const QMap<QString, QString>& programMap);
signals:
    void macroCreated(const QJsonObject &entry);

};

#endif // ADDCOMBINATIONFRAGMENT_H
