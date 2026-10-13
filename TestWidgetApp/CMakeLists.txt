cmake_minimum_required(VERSION 3.16)

project(TestWidgetApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ОБЯЗАТЕЛЬНО запрашиваем и Widgets, и Gui
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TestWidgetApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(TestWidgetApp SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(TestWidgetApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# === ПОДКЛЮЧЕНИЕ НАШЕГО КАСТОМНОГО ВИДЖЕТА ===
# 1. Говорим компилятору, где искать заголовочный файл (mycustomwidget.h)
target_include_directories(TestWidgetApp PRIVATE "C:/MyWidgetKit/include")

# 2. Связываем программу с Qt модулями и файлом линковки нашего виджета
target_link_libraries(TestWidgetApp PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    "C:/MyWidgetKit/debug/libMyCustomWidget.dll.a"
)
# =============================================

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TestWidgetApp)
endif()
set_target_properties(TestWidgetApp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TestWidgetApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TestWidgetApp)
endif()
