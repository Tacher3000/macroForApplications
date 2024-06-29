#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include <QStringList>
#include <QString>

class ProgramManager {
public:
    virtual ~ProgramManager() = default;

    // Метод для получения списка установленных программ
    virtual QStringList ListInstalledPrograms() = 0;

    // Метод для получения иконки программы по пути
    virtual QString GetProgramIconPath(const QString& programName) = 0;
    virtual QMap<QString, QString> ListInstalledProgramsWithIcons() = 0;
    virtual QString GetProgramInstallPath(const QString &programName) = 0;
};

#endif // PROGRAMMANAGER_H
