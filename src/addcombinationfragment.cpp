#include "addcombinationfragment.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFont>
#include <QDir>
#include <QDebug>
#include <QComboBox>
#include <QJsonArray>
#include "screens.h"

AddCombinationFragment::AddCombinationFragment(QWidget *parent)
    : BaseFragment(parent)
{
}

void AddCombinationFragment::init()
{
// Инициализация менеджера программ и JSON
#ifdef _WIN32
    programManager = std::make_unique<WindowsProgramManager>();
#elif __linux__
    // programManager = std::make_unique<LinuxProgramManager>();
#endif
    jsonManipulator = new JsonArrayManipulations("config/configure.json");

    mainLayout = new QGridLayout(this);

    // setStyleSheet(
    //     "QFrame { background-color: #f0f0f0; border-radius: 10px; }"
    //     "QLineEdit, QComboBox { border: 2px solid #4a90e2; border-radius: 5px; padding: 5px; font-size: 14px; }"
    //     "QPushButton { background-color: #4a90e2; color: white; border-radius: 5px; padding: 8px; font-size: 14px; }"
    //     "QPushButton:hover { background-color: #357abd; }"
    //     "QLabel { font-size: 14px; color: #333; }"
    //     );

    // Поля ввода
    QLabel *shortcutLabel = new QLabel("Keyboard Shortcut:", this);
    keyboardShortcut = new KeyLineEdit(this);
    keyboardShortcut->setPlaceholderText(tr("e.g., Ctrl+Shift+Q"));
    keyboardShortcut->setMinimumSize(400, 50);
    keyboardShortcut->setAlignment(Qt::AlignCenter);

    QLabel *titleLabel = new QLabel("Title:", this);
    titleLineEdit = new QLineEdit(this);
    titleLineEdit->setPlaceholderText(tr("Enter title"));
    titleLineEdit->setMinimumSize(400, 50);
    titleLineEdit->setAlignment(Qt::AlignCenter);

    QLabel *appLabel = new QLabel("Select Application or File:", this);
    applications = new QComboBox(this);
    fillComboBoxWithPrograms(programManager->ListInstalledProgramsWithIcons());
    applications->setMinimumSize(400, 50);

    QLabel *fileLabel = new QLabel("File Path:", this);
    filePathEdit = new QLineEdit(this);
    filePathEdit->setPlaceholderText(tr("Select a file or leave blank"));
    filePathEdit->setMinimumSize(300, 50);

    fileSelectionButton = new QPushButton("...", this);
    fileSelectionButton->setMinimumSize(50, 50);
    connect(fileSelectionButton, &QPushButton::clicked, this, &AddCombinationFragment::chooseFile);

    saveButton = new QPushButton("Save", this);
    saveButton->setMinimumSize(400, 50);
    connect(saveButton, &QPushButton::clicked, this, &AddCombinationFragment::saveCombination);

    mainLayout->addWidget(shortcutLabel, 0, 0);
    mainLayout->addWidget(keyboardShortcut, 0, 1, 1, 2);
    mainLayout->addWidget(titleLabel, 1, 0);
    mainLayout->addWidget(titleLineEdit, 1, 1, 1, 2);
    mainLayout->addWidget(appLabel, 2, 0);
    mainLayout->addWidget(applications, 2, 1, 1, 2);
    mainLayout->addWidget(fileLabel, 3, 0);
    mainLayout->addWidget(filePathEdit, 3, 1);
    mainLayout->addWidget(fileSelectionButton, 3, 2);
    mainLayout->addWidget(saveButton, 4, 1, 1, 2);

    QPushButton *backButton = new QPushButton("Back", this);
    backButton->setMinimumSize(400, 50);
    backButton->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border-radius: 5px; padding: 8px; font-size: 14px; }"
                              "QPushButton:hover { background-color: #c0392b; }");
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit navigateTo(screens::MAIN_TAG);
    });
    mainLayout->addWidget(backButton, 5, 1, 1, 2);

    setLayout(mainLayout);
}

void AddCombinationFragment::fillComboBoxWithPrograms(const QMap<QString, QString>& programMap)
{
    applications->clear();
    for (auto it = programMap.begin(); it != programMap.end(); ++it) {
        QString programName = it.key();
        QString iconPath = it.value();
        QIcon icon;
        if (!iconPath.isEmpty()) {
            icon = QIcon(iconPath);
        }
        applications->addItem(icon, programName);
    }
}

void AddCombinationFragment::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select a File"), "", "All Files (*.*)");
    filePathEdit->setText(filePath);
}

void AddCombinationFragment::saveCombination()
{
    QString keyboard = keyboardShortcut->text().trimmed();
    QString title = titleLineEdit->text().trimmed();
    QString filePath = filePathEdit->text().trimmed();

    qDebug() << "Saving combination - Keyboard:" << keyboard << ", Title:" << title << ", FilePath:" << filePath;

    if (keyboard.isEmpty() || title.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Keyboard shortcut and title are required."));
        qDebug() << "Validation failed: Keyboard or title is empty.";
        return;
    }

    // Простая валидация формата (например, содержит модификаторы + клавишу)
    QStringList parts = keyboard.split("+", Qt::SkipEmptyParts);
    if (parts.size() < 1 || parts.size() > 4) { // Ограничиваем до 3 модификаторов + клавиша
        QMessageBox::warning(this, tr("Error"), tr("Invalid keyboard shortcut format. Use Ctrl+Shift+Q, etc."));
        qDebug() << "Validation failed: Invalid format:" << keyboard;
        return;
    }

    QJsonObject newEntry;
    newEntry.insert("keyboardShortcut", keyboard);
    newEntry.insert("title", title);

    if (!filePath.isEmpty()) {
        newEntry.insert("filePath", filePath);
        qDebug() << "Added file path to entry:" << filePath;
    } else {
        QString programName = applications->currentText();
        if (!programName.isEmpty()) {
            QString iconPath = programManager->GetProgramIconPath(programName);
            QString installPath = programManager->GetProgramInstallPath(programName);
            QFileInfo fileInfo(installPath);
            newEntry.insert("programName", programName);
            newEntry.insert("iconPath", iconPath);
            newEntry.insert("installPath", installPath);
            qDebug() << "Added program - Name:" << programName << ", InstallPath:" << installPath;
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Please select a program or file."));
            qDebug() << "Validation failed: No program or file selected.";
            return;
        }
    }

    if (!jsonManipulator->addEntry(newEntry)) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to save the combination."));
        qDebug() << "Failed to save entry to JSON.";
    } else {
        qDebug() << "Successfully saved entry to JSON:" << newEntry;
        emit macroCreated(newEntry);
        QMessageBox::information(this, tr("Success"), tr("Combination saved successfully!"));
        emit navigateTo(screens::MAIN_TAG);
    }
}
