#ifndef CENTRALWINDOW_H
#define CENTRALWINDOW_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "createmacrodialog.h"
#include "JsonArrayManipulations.h"
#include "EntryWidget.h"
#include "shortcutmanager.h"

/**
 * @class CentralWindow
 * @brief Main widget for the application's central window.
 *
 * The CentralWindow class is responsible for managing the main layout of the application.
 * It contains the main layout, a button to add macros, a dialog for creating macros,
 * a shortcut manager, and an object for JSON array manipulations. It also handles
 * loading entries and adding entries to both the layout and the shortcut manager.
 *
 * @class CentralWindow
 * @brief Центральный виджет для главного окна приложения.
 *
 * Класс CentralWindow отвечает за управление основным макетом приложения.
 * Он содержит основной макет, кнопку для добавления макросов, диалог для создания макросов,
 * менеджер ярлыков и объект для манипуляций с JSON массивами. Также он обрабатывает
 * загрузку записей и добавление записей в макет и менеджер ярлыков.
 */

class CentralWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a CentralWindow object.
     * @param parent Pointer to the parent widget, if any.
     *
     * @brief Конструктор объекта CentralWindow.
     * @param parent Указатель на родительский виджет, если есть.
     */
    CentralWindow(QWidget *parent = nullptr);
private:
    QVBoxLayout *mainLayout;            ///< Main vertical layout of the application
                                        ///< Основной вертикальный макет приложения
    QPushButton *addMacroButton;        ///< Button to add new macros
                                        ///< Кнопка для добавления новых макросов
    CreateMacroDialog *macroDialog;     ///< Dialog to create macros
                                        ///< Диалог для создания макросов
    ShortcutManager *manager;           ///< Manager for handling shortcuts
                                        ///< Менеджер для управления ярлыками

    JsonArrayManipulations *jsonArrayManipulations;     ///< Object for JSON array manipulations
                                                        ///< Объект для манипуляций с JSON массивами

    /**
     * @brief Loads entries from a file or other source.
     *
     * @brief Загружает записи из файла.
     */
    void loadEntries();

    /**
     * @brief Adds an entry to the layout.
     * @param entry JSON object representing the entry to be added.
     *
     * @brief Добавляет запись в макет.
     * @param entry JSON объект, представляющий добавляемую запись.
     */
    void addEntryToLayout(const QJsonObject &entry);

    /**
     * @brief Adds an entry to the shortcut manager.
     * @param entry JSON object representing the entry to be added.
     *
     * @brief Добавляет запись в менеджер ярлыков.
     * @param entry JSON объект, представляющий добавляемую запись.
     */
    void addEntryToManager(const QJsonObject &entry);
};

#endif // CENTRALWINDOW_H
