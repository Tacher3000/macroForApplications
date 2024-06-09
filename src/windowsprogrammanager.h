#ifndef WINDOWSPROGRAMMANAGER_H
#define WINDOWSPROGRAMMANAGER_H

#include "programmanager.h"
#include <windows.h>
#include <QDebug>
#include <QStringList>

class WindowsProgramManager : public ProgramManager
{
public:
    WindowsProgramManager();
    QStringList ListInstalledPrograms() override;
    QString GetProgramIconPath(const QString& programName) override;
    QMap<QString, QString> ListInstalledProgramsWithIcons() override;
};

#endif // WINDOWSPROGRAMMANAGER_H
