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
#include <QVector>

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

    QGridLayout *main_layout;

    QLineEdit *keyboard_shortcut;

    QLineEdit *title_line_edit;

    QLineEdit *file_way_edit;
    QPushButton *file_selection_button;

    QPushButton *add_button;
};

#endif // CREATEMACRODIALOG_H
