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

/**
 * @class CreateMacroDialog
 * @brief Dialog for creating macros.
 *
 * The CreateMacroDialog class provides a dialog interface for creating and saving macros.
 * It includes fields for entering a title, selecting a file, and setting a keyboard shortcut.
 * The class interacts with a ProgramManager to populate a сomboBox with available programs.
 *
 * @class CreateMacroDialog
 * @brief Диалог для создания макросов.
 *
 * Класс CreateMacroDialog предоставляет интерфейс диалога для создания и сохранения макросов.
 * Он включает поля для ввода заголовка, выбора файла и установки клавиатурного ярлыка.
 * Класс взаимодействует с ProgramManager для заполнения сomboBox доступными программами.
 */

class CreateMacroDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a CreateMacroDialog object.
     * @param parent Pointer to the parent widget, if any.
     *
     * @brief Конструктор объекта CreateMacroDialog.
     * @param parent Указатель на родительский виджет, если есть.
     */
    CreateMacroDialog(QWidget *parent = nullptr);

    /**
     * @brief Fills the combo box with available programs.
     * @param programMap A map containing program names and paths.
     *
     * @brief Заполняет комбобокс доступными программами.
     * @param programMap Карта, содержащая имена программ и пути к ним.
     */
    void fillComboBoxWithPrograms(const QMap<QString, QString>& programMap);
private slots:
    /**
     * @brief Opens a file dialog to choose a file.
     *
     * @brief Открывает диалоговое окно для выбора файла.
     */
    void chooseFile();
//    void saveDataToVector();

    /**
     * @brief Saves the macro data to a JSON file.
     *
     * @brief Сохраняет данные макроса в JSON файл.
     */
    void saveDataToJsonFile();

private:
    QGridLayout *mainLayout;                ///< Main layout of the dialog
                                            ///< Основной макет диалога

    KeyLineEdit *keyboardShortcut;          ///< Line edit for entering keyboard shortcuts
                                            ///< Поле для ввода клавиатурных ярлыков

    QLineEdit *titleLineEdit;               ///< Line edit for entering the title
                                            ///< Поле для ввода заголовка

    QComboBox *applications;                ///< Combo box for selecting applications
                                            ///< Комбобокс для выбора приложений

    QLineEdit *fileWayEdit;                 ///< Line edit for displaying selected file path
                                            ///< Поле для отображения выбранного пути к файлу
    QPushButton *fileSelectionButton;       ///< Button to open file dialog
                                            ///< Кнопка для открытия диалогового окна выбора файла

    QPushButton *addButton;                 ///< Button to add the macro
                                            ///< Кнопка для добавления макроса

    std::unique_ptr<ProgramManager> _programManager;    ///< Pointer to the ProgramManager object
                                                        ///< Указатель на объект ProgramManager


};

#endif // CREATEMACRODIALOG_H
