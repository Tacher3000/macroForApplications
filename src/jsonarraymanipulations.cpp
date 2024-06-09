#include "JsonArrayManipulations.h"

JsonArrayManipulations::JsonArrayManipulations(const QString &filePath) : filePath(filePath)
{
    QString directoryPath = QFileInfo(filePath).path();
    if (!QDir(directoryPath).exists()) {
        QDir().mkdir(directoryPath);
    }
}

bool JsonArrayManipulations::addEntry(const QJsonObject &entry)
{
    QJsonObject jsonObject = readJsonFromFile();
    QJsonArray entries = jsonObject.value("entries").toArray();
    entries.append(entry);
    jsonObject.insert("entries", entries);
    return writeJsonToFile(jsonObject);
}

QJsonArray JsonArrayManipulations::getEntries() const
{
    QJsonObject jsonObject = readJsonFromFile();
    return jsonObject.value("entries").toArray();
}

QJsonObject JsonArrayManipulations::readJsonFromFile() const
{
    QFile file(filePath);
    if (!file.exists()) {
        return QJsonObject();
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file for reading:" << file.errorString();
        return QJsonObject();
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    return jsonDoc.object();
}

bool JsonArrayManipulations::writeJsonToFile(const QJsonObject &jsonObject) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file for writing:" << file.errorString();
        return false;
    }

    QJsonDocument jsonDoc(jsonObject);
    file.write(jsonDoc.toJson());
    file.close();
    return true;
}
