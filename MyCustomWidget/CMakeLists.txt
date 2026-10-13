cmake_minimum_required(VERSION 3.16)

project(MyCustomWidget LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. ОБЯЗАТЕЛЬНО добавляем компонент Widgets (без него ui_*.h файл не сгенерируется)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets)

# 2. Убираем дублирование файлов
add_library(MyCustomWidget SHARED
  MyCustomWidget_global.h
  mycustomwidget.h
  mycustomwidget.cpp
  mycustomwidget.ui
)

# 3. Линкуем модуль Widgets к библиотеке
target_link_libraries(MyCustomWidget PRIVATE
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_compile_definitions(MyCustomWidget PRIVATE MYCUSTOMWIDGET_LIBRARY)
