#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include <QStringList>

class ProgramManager {
public:
    virtual ~ProgramManager() = default;

    // Метод для получения списка установленных программ
    virtual QStringList ListInstalledPrograms() = 0;

    // Метод для получения иконки программы по пути
    // virtual std::string GetProgramIconPath(const std::string& programName) = 0;
};

#endif // PROGRAMMANAGER_H
