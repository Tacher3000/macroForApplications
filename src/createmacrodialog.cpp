#include "../include/createmacrodialog.h"

CreateMacroDialog::CreateMacroDialog(QWidget *parent) : QDialog(parent)
{
    main_layout = new QGridLayout(this);

    keyboard_shortcut = new QLineEdit(this);
    keyboard_shortcut->setMinimumSize(400, 50);

    title_line_edit = new QLineEdit(this);
    title_line_edit->setMinimumSize(400, 50);

    file_way_edit = new QLineEdit(this);
    file_way_edit->setMinimumSize(300, 50);

    file_selection_button = new QPushButton(this);
    file_selection_button->setMinimumSize(50, 50);

    main_layout->addWidget(keyboard_shortcut, 0, 0, 1, 2);
    main_layout->addWidget(title_line_edit, 1, 0, 1, 2);
    main_layout->addWidget(file_way_edit, 3, 0, 1, 1);
    main_layout->addWidget(file_selection_button, 3, 1, 1, 1);

}
