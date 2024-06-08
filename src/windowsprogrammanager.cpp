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

    // Открываем ключ реестра с информацией об установленных программах
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hUninstallKey) != ERROR_SUCCESS) {
        qDebug() << "Error opening registry key.";
        return programmList;
    }

    // Перебираем все подчиненные ключи
    while (RegEnumKeyExA(hUninstallKey, dwIndex, szSubKey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
        // Открываем каждый подчиненный ключ
        if (RegOpenKeyExA(hUninstallKey, szSubKey, 0, KEY_READ, &hAppKey) == ERROR_SUCCESS) {
            // Читаем значение DisplayName
            if (RegQueryValueExA(hAppKey, "DisplayName", NULL, &dwType, (LPBYTE)szDisplayName, &dwDisplayNameSize) == ERROR_SUCCESS) {
                programmList << szDisplayName;
            }
            // Закрываем подчиненный ключ
            RegCloseKey(hAppKey);
        }
        // Переходим к следующему ключу
        dwIndex++;
        dwSize = MAX_PATH;
        dwDisplayNameSize = MAX_PATH;
    }
    // Закрываем основной ключ
    RegCloseKey(hUninstallKey);
    return programmList;
}
