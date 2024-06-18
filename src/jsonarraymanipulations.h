#ifndef JSONARRAYMANIPULATIONS_H
#define JSONARRAYMANIPULATIONS_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDebug>

/**
 * @class JsonArrayManipulations
 * @brief A class for manipulating JSON arrays stored in a file.
 *
 * The JsonArrayManipulations class provides methods to read, write, and modify JSON arrays
 * stored in a specified file. It allows adding entries to the JSON array and retrieving
 * all entries.
 *
 * @class JsonArrayManipulations
 * @brief Класс для манипуляции JSON массивами, хранящимися в файле.
 *
 * Класс JsonArrayManipulations предоставляет методы для чтения, записи и изменения JSON массивов,
 * хранящихся в указанном файле. Он позволяет добавлять записи в JSON массив и получать все записи.
 */

class JsonArrayManipulations
{
public:
    /**
     * @brief Constructs a JsonArrayManipulations object with the specified file path.
     * @param filePath The path to the JSON file.
     *
     * @brief Конструктор объекта JsonArrayManipulations с указанным путем к файлу.
     * @param filePath Путь к JSON файлу.
     */
    JsonArrayManipulations(const QString &filePath);

    /**
     * @brief Adds an entry to the JSON array.
     * @param entry The JSON object to add to the array.
     * @return True if the entry was successfully added, false otherwise.
     *
     * @brief Добавляет запись в JSON массив.
     * @param entry JSON объект для добавления в массив.
     * @return True если запись была успешно добавлена, false в противном случае.
     */
    bool addEntry(const QJsonObject &entry);

    /**
     * @brief Retrieves all entries from the JSON array.
     * @return A QJsonArray containing all entries.
     *
     * @brief Получает все записи из JSON массива.
     * @return QJsonArray, содержащий все записи.
     */
    QJsonArray getEntries() const;

private:
    QString filePath;   ///< Path to the JSON file
                        ///< Путь к JSON файлу

    /**
     * @brief Reads the JSON object from the file.
     * @return The JSON object read from the file.
     *
     * @brief Считывает JSON объект из файла.
     * @return JSON объект, считанный из файла.
     */
    QJsonObject readJsonFromFile() const;

    /**
     * @brief Writes the JSON object to the file.
     * @param jsonObject The JSON object to write to the file.
     * @return True if the JSON object was successfully written, false otherwise.
     *
     * @brief Записывает JSON объект в файл.
     * @param jsonObject JSON объект для записи в файл.
     * @return True если JSON объект был успешно записан, false в противном случае.
     */
    bool writeJsonToFile(const QJsonObject &jsonObject) const;
};

#endif // JSONARRAYMANIPULATIONS_H
