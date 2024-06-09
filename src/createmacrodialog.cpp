#include "createmacrodialog.h"



CreateMacroDialog::CreateMacroDialog(QWidget *parent) : QDialog(parent)
{
    #ifdef _WIN32
        _programManager = std::make_unique<WindowsProgramManager>();
    #elif __linux__
        // _programManager = std::make_unique<LinuxProgramManager>();
    #endif


    mainLayout = new QGridLayout(this);
    QFont font;
    font.setPointSize(14);

    keyboardShortcut = new KeyLineEdit(this);
    keyboardShortcut->setMinimumSize(400, 50);
    keyboardShortcut->setPlaceholderText("Комбинацияя клавиш");
    keyboardShortcut->setAlignment(Qt::AlignCenter);
    keyboardShortcut->setFont(font);

    titleLineEdit = new QLineEdit(this);
    titleLineEdit->setMinimumSize(400, 50);
    titleLineEdit->setPlaceholderText("Название");
    titleLineEdit->setAlignment(Qt::AlignCenter);
    titleLineEdit->setFont(font);

    applications = new QComboBox(this);
    // applications->addItems(_programManager->ListInstalledPrograms());
    fillComboBoxWithPrograms(_programManager->ListInstalledProgramsWithIcons());
    applications->setMinimumSize(400, 50);
    applications->setMaximumSize(400, 50); // исправить
    applications->setFont(font);

    fileWayEdit = new QLineEdit(this);
    fileWayEdit->setMinimumSize(300, 50);
    fileWayEdit->setPlaceholderText("Путь");
    fileWayEdit->setFont(font);

    fileSelectionButton = new QPushButton(this);
    fileSelectionButton->setMinimumSize(50, 50);
    QObject::connect(fileSelectionButton, &QPushButton::clicked, this, &CreateMacroDialog::chooseFile);

    addButton = new QPushButton(this);
    addButton->setMinimumSize(400, 50);
    addButton->setText("Добавить");
    addButton->setFont(font);
    QObject::connect(addButton, &QPushButton::clicked, this, &CreateMacroDialog::saveDataToJsonFile);

    mainLayout->addWidget(keyboardShortcut, 0, 0, 1, 2);
    mainLayout->addWidget(titleLineEdit, 1, 0, 1, 2);
    mainLayout->addWidget(applications, 2, 0, 1, 2);
    mainLayout->addWidget(fileWayEdit, 3, 0, 1, 1);
    mainLayout->addWidget(fileSelectionButton, 3, 1, 1, 1);
    mainLayout->addWidget(addButton, 4, 0, 1, 2);
}

void CreateMacroDialog::fillComboBoxWithPrograms(const QMap<QString, QString> &programMap)
{
    applications->clear();

    for (auto it = programMap.begin(); it != programMap.end(); ++it) {
        QString programName = it.key();
        QString iconPath = it.value();

        qDebug() << iconPath;

        QIcon icon;
        if (!iconPath.isEmpty()) {
            icon = QIcon(iconPath);
        }
        applications->addItem(icon, programName);
    }
}

void CreateMacroDialog::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл", "", "All Files (*)");
    fileWayEdit->setText(filePath);
}

void CreateMacroDialog::saveDataToJsonFile()
{
    QString directoryPath = "config/";
    if (!QDir(directoryPath).exists()) {
        (QDir().mkdir(directoryPath));
    }

    QString filename = "config/configure.json";

    QJsonObject jsonObject;

    QString keyboard = keyboardShortcut->text();
    QString title = titleLineEdit->text();
    QString filePath = fileWayEdit->text();

    jsonObject.insert("keyboardShortcut", keyboard);
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
