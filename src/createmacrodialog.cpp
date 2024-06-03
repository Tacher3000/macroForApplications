#include "createmacrodialog.h"



CreateMacroDialog::CreateMacroDialog(QWidget *parent) : QDialog(parent)
{
    main_layout = new QGridLayout(this);
    QFont font;
    font.setPointSize(14);

    keyboard_shortcut = new QLineEdit(this);
    keyboard_shortcut->setMinimumSize(400, 50);
    keyboard_shortcut->setPlaceholderText("Комбинацияя клавиш");
    keyboard_shortcut->setAlignment(Qt::AlignCenter);
    keyboard_shortcut->setFont(font);

    title_line_edit = new QLineEdit(this);
    title_line_edit->setMinimumSize(400, 50);
    title_line_edit->setPlaceholderText("Название");
    title_line_edit->setAlignment(Qt::AlignCenter);
    title_line_edit->setFont(font);

    file_way_edit = new QLineEdit(this);
    file_way_edit->setMinimumSize(300, 50);
    file_way_edit->setPlaceholderText("Путь");
    file_way_edit->setFont(font);

    file_selection_button = new QPushButton(this);
    file_selection_button->setMinimumSize(50, 50);
    QObject::connect(file_selection_button, &QPushButton::clicked, this, &CreateMacroDialog::chooseFile);

    add_button = new QPushButton(this);
    add_button->setMinimumSize(400, 50);
    add_button->setText("Добавить");
    add_button->setFont(font);
    QObject::connect(add_button, &QPushButton::clicked, this, &CreateMacroDialog::saveDataToJsonFile);

    main_layout->addWidget(keyboard_shortcut, 0, 0, 1, 2);
    main_layout->addWidget(title_line_edit, 1, 0, 1, 2);
    main_layout->addWidget(file_way_edit, 3, 0, 1, 1);
    main_layout->addWidget(file_selection_button, 3, 1, 1, 1);
    main_layout->addWidget(add_button, 4, 0, 1, 2);
}

void CreateMacroDialog::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл", "", "All Files (*)");
    file_way_edit->setText(filePath);
}

void CreateMacroDialog::saveDataToJsonFile()
{
    QString directoryPath = "config/";
    if (!QDir(directoryPath).exists()) {
        (QDir().mkdir(directoryPath));
    }

    QString filename = "config/configure.json";

    QJsonObject jsonObject;

    QString keyboardShortcut = keyboard_shortcut->text();
    QString title = title_line_edit->text();
    QString filePath = file_way_edit->text();

    jsonObject.insert("keyboardShortcut", keyboardShortcut);
    jsonObject.insert("title", title);
    jsonObject.insert("filePath", filePath);

    QJsonDocument jsonDoc(jsonObject);

    QFile file(filename);
//    if (!file.open(QIODevice::WriteOnly)) {
//        QMessageBox::critical(nullptr, "Ошибка", QString("Не удалось открыть файл для записи: %1").arg(file.errorString()));
//        return;
//    }

    file.write(jsonDoc.toJson());

    file.close();
}
