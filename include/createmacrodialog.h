#ifndef CREATEMACRODIALOG_H
#define CREATEMACRODIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

class CreateMacroDialog : public QDialog
{
    Q_OBJECT
public:
    CreateMacroDialog(QWidget *parent = nullptr);
private:
    QGridLayout *main_layout;

    QLineEdit *keyboard_shortcut;

    QLineEdit *title_line_edit;

    QLineEdit *file_way_edit;
    QPushButton *file_selection_button;
};

#endif // CREATEMACRODIALOG_H
