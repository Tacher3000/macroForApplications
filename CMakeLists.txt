cmake_minimum_required(VERSION 3.5)

project(macroForApplications VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)

set(PROJECT_SOURCES
        main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(macroForApplications
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


        CMakeLists.txt main.cpp src/mainwindow.cpp src/mainwindow.h
        src/createmacrodialog.h src/createmacrodialog.cpp
        resources/resources.qrc
        src/jsonarraymanipulations.h src/jsonarraymanipulations.cpp
        src/centralwindow.h src/centralwindow.cpp
        src/keylineedit.h src/keylineedit.cpp
        src/programmanager.h src/programmanager.cpp
        src/windowsprogrammanager.h src/windowsprogrammanager.cpp
        src/entrywidget.h src/entrywidget.cpp
        src/shortcutmanager.h src/shortcutmanager.cpp
        src/globalhotkeymanager.h src/globalhotkeymanager.cpp
        src/windowsglobalhotkeymanager.h src/windowsglobalhotkeymanager.cpp
        src/mainfragment.h src/mainfragment.cpp
        src/basefragment.h
        src/basescreensfactory.h
        src/screensfactory.h src/screensfactory.cpp
        src/navigator.h src/navigator.cpp
        src/addcombinationfragment.h src/addcombinationfragment.cpp
        src/settingsfragment.h src/settingsfragment.cpp
        src/screens.h src/screens.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET macroForApplications APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(macroForApplications SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(macroForApplications
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(macroForApplications PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(macroForApplications PRIVATE Qt6::Gui)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.macroForApplications)
endif()
set_target_properties(macroForApplications PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS macroForApplications
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(macroForApplications)
endif()
