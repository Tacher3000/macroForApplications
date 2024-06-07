#include "src/mainwindow.h"

#include <QApplication>

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <cstdlib>
#include <cstdio>
#endif

void ListInstalledPrograms() {
#ifdef _WIN32
    HKEY hUninstallKey = NULL;
    HKEY hAppKey = NULL;
    DWORD dwIndex = 0;
    CHAR szSubKey[MAX_PATH];
    DWORD dwSize = MAX_PATH;
    CHAR szDisplayName[MAX_PATH];
    DWORD dwType = 0;
    DWORD dwDisplayNameSize = MAX_PATH;

    // Открытие ключа реестра, где хранятся данные об установленных программах
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hUninstallKey) != ERROR_SUCCESS) {
        std::cerr << "Error opening registry key." << std::endl;
        return;
    }

    // Перебор всех подпапок в ключе реестра
    while (RegEnumKeyExA(hUninstallKey, dwIndex, szSubKey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
        // Открытие каждой подпапки
        if (RegOpenKeyExA(hUninstallKey, szSubKey, 0, KEY_READ, &hAppKey) == ERROR_SUCCESS) {
            // Получение значения "DisplayName" из подпапки
            if (RegQueryValueExA(hAppKey, "DisplayName", NULL, &dwType, (LPBYTE)szDisplayName, &dwDisplayNameSize) == ERROR_SUCCESS) {
                qDebug() << "Installed Program: " << szDisplayName;
            }
            // Закрытие открытого ключа реестра
            RegCloseKey(hAppKey);
        }
        // Переход к следующему ключу
        dwIndex++;
        dwSize = MAX_PATH;
        dwDisplayNameSize = MAX_PATH;
    }
    // Закрытие основного ключа реестра
    RegCloseKey(hUninstallKey);

#elif __linux__
    // Открытие процесса для выполнения команды `dpkg -l`
    FILE* fp = popen("dpkg -l | grep '^ii' | awk '{print $2 \" \" $3}'", "r");
    if (fp == nullptr) {
        std::cerr << "Failed to run command\n";
        return;
    }

    char path[1035];
    // Чтение вывода команды построчно
    while (fgets(path, sizeof(path), fp) != NULL) {
        qDebug() << "Installed Program: " << path;
    }
    // Закрытие потока
    pclose(fp);
#endif
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    ListInstalledPrograms();

    return a.exec();
}
