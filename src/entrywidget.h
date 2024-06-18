#ifndef ENTRYWIDGET_H
#define ENTRYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QJsonObject>

/**
 * @class EntryWidget
 * @brief A widget that displays a macro entry.
 *
 * The EntryWidget class represents a widget that displays information about a macro entry.
 * It includes labels for the icon, shortcut, program name, and title of the macro.
 *
 * @class EntryWidget
 * @brief Виджет для отображения записи макроса.
 *
 * Класс EntryWidget представляет виджет, отображающий информацию о записи макроса.
 * Он включает метки для значка, ярлыка, имени программы и заголовка макроса.
 */
class EntryWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs an EntryWidget object.
     * @param entry JSON object representing the macro entry.
     * @param parent Pointer to the parent widget, if any.
     *
     * @brief Конструктор объекта EntryWidget.
     * @param entry JSON объект, представляющий запись макроса.
     * @param parent Указатель на родительский виджет, если есть.
     */
    EntryWidget(const QJsonObject &entry, QWidget *parent = nullptr);

private:
    QLabel *iconLabel;          ///< Label to display the icon of the macro
                                ///< Метка для отображения значка макроса
    QLabel *shortcutLabel;      ///< Label to display the shortcut of the macro
                                ///< Метка для отображения ярлыка макроса
    QLabel *programNameLabel;   ///< Label to display the program name of the macro
                                ///< Метка для отображения имени программы макроса
    QLabel *titleLabel;         ///< Label to display the title of the macro
                                ///< Метка для отображения заголовка макроса
};

#endif // ENTRYWIDGET_H
