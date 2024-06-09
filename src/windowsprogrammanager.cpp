#include "windowsprogrammanager.h"

WindowsProgramManager::WindowsProgramManager() {}

QStringList WindowsProgramManager::ListInstalledPrograms()
{
    QStringList programmList;

    HKEY hUninstallKey = NULL;
    HKEY hAppKey = NULL;
    DWORD dwIndex = 0;
    CHAR szSubKey[MAX_PATH];
    DWORD dwSize = MAX_PATH;
    CHAR szDisplayName[MAX_PATH];
    CHAR szDisplayIcon[MAX_PATH];
    DWORD dwType = 0;
    DWORD dwDisplayNameSize = MAX_PATH;
    DWORD dwDisplayIconSize = MAX_PATH;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hUninstallKey) != ERROR_SUCCESS) {
        qDebug() << "Error opening registry key.";
        return programmList;
    }

    while (RegEnumKeyExA(hUninstallKey, dwIndex, szSubKey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
        if (RegOpenKeyExA(hUninstallKey, szSubKey, 0, KEY_READ, &hAppKey) == ERROR_SUCCESS) {
            if (RegQueryValueExA(hAppKey, "DisplayName", NULL, &dwType, (LPBYTE)szDisplayName, &dwDisplayNameSize) == ERROR_SUCCESS) {
                programmList << szDisplayName;
            }
            RegCloseKey(hAppKey);
        }
        dwIndex++;
        dwSize = MAX_PATH;
        dwDisplayNameSize = MAX_PATH;
    }
    RegCloseKey(hUninstallKey);
    return programmList;
}

QString WindowsProgramManager::GetProgramIconPath(const QString &programName)
{
    HKEY hUninstallKey = NULL;
    HKEY hAppKey = NULL;
    DWORD dwIndex = 0;
    CHAR szSubKey[MAX_PATH];
    DWORD dwSize = MAX_PATH;
    CHAR szDisplayName[MAX_PATH];
    CHAR szDisplayIcon[MAX_PATH];
    DWORD dwType = 0;
    DWORD dwDisplayNameSize = MAX_PATH;
    DWORD dwDisplayIconSize = MAX_PATH;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hUninstallKey) != ERROR_SUCCESS) {
        qDebug() << "Error opening registry key.";
        return "";
    }

    while (RegEnumKeyExA(hUninstallKey, dwIndex, szSubKey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
        if (RegOpenKeyExA(hUninstallKey, szSubKey, 0, KEY_READ, &hAppKey) == ERROR_SUCCESS) {
            if (RegQueryValueExA(hAppKey, "DisplayName", NULL, &dwType, (LPBYTE)szDisplayName, &dwDisplayNameSize) == ERROR_SUCCESS) {
                if (programName == QString::fromLocal8Bit(szDisplayName)) {
                    if (RegQueryValueExA(hAppKey, "DisplayIcon", NULL, &dwType, (LPBYTE)szDisplayIcon, &dwDisplayIconSize) == ERROR_SUCCESS) {
                        RegCloseKey(hAppKey);
                        RegCloseKey(hUninstallKey);
                        return QString::fromLocal8Bit(szDisplayIcon);
                    }
                }
            }
            RegCloseKey(hAppKey);
        }
        dwIndex++;
        dwSize = MAX_PATH;
        dwDisplayNameSize = MAX_PATH;
        dwDisplayIconSize = MAX_PATH;
    }
    RegCloseKey(hUninstallKey);
    return "";
}

QMap<QString, QString> WindowsProgramManager::ListInstalledProgramsWithIcons()
{
    QMap<QString, QString> programMap;

    HKEY hUninstallKey = NULL;
    HKEY hAppKey = NULL;
    DWORD dwIndex = 0;
    CHAR szSubKey[MAX_PATH];
    DWORD dwSize = MAX_PATH;
    CHAR szDisplayName[MAX_PATH];
    CHAR szDisplayIcon[MAX_PATH];
    DWORD dwType = 0;
    DWORD dwDisplayNameSize = MAX_PATH;
    DWORD dwDisplayIconSize = MAX_PATH;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hUninstallKey) != ERROR_SUCCESS) {
        qDebug() << "Error opening registry key.";
        return programMap;
    }

    while (RegEnumKeyExA(hUninstallKey, dwIndex, szSubKey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
        if (RegOpenKeyExA(hUninstallKey, szSubKey, 0, KEY_READ, &hAppKey) == ERROR_SUCCESS) {
            if (RegQueryValueExA(hAppKey, "DisplayName", NULL, &dwType, (LPBYTE)szDisplayName, &dwDisplayNameSize) == ERROR_SUCCESS) {
                QString displayName = QString::fromLocal8Bit(szDisplayName);
                QString displayIcon;

                dwDisplayIconSize = MAX_PATH;
                if (RegQueryValueExA(hAppKey, "DisplayIcon", NULL, &dwType, (LPBYTE)szDisplayIcon, &dwDisplayIconSize) == ERROR_SUCCESS) {
                    displayIcon = QString::fromLocal8Bit(szDisplayIcon);
                }

                programMap[displayName] = displayIcon;
            }
            RegCloseKey(hAppKey);
        }
        dwIndex++;
        dwSize = MAX_PATH;
        dwDisplayNameSize = MAX_PATH;
    }
    RegCloseKey(hUninstallKey);
    return programMap;
}
