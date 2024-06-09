#ifndef JSONARRAYMANIPULATIONS_H
#define JSONARRAYMANIPULATIONS_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDebug>

class JsonArrayManipulations
{
public:
    JsonArrayManipulations(const QString &filePath);
    bool addEntry(const QJsonObject &entry);
    QJsonArray getEntries() const;

private:
    QString filePath;
    QJsonObject readJsonFromFile() const;
    bool writeJsonToFile(const QJsonObject &jsonObject) const;
};

#endif // JSONARRAYMANIPULATIONS_H
