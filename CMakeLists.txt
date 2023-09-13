cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME NMR_Processing)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(INCLUDE_DIRECTORIES dependencies/QCustomPlot)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS PrintSupport Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.h            mainwindow.cpp
        plotwidget.h            plotwidget.cpp
        processwidget.h         processwidget.cpp
        baseprocesswidget.h     baseprocesswidget.cpp
        tikhonovprocesswidget.h tikhonovprocesswidget.cpp
        filesystemwidget.h      filesystemwidget.cpp
        logwidget.h             logwidget.cpp

        baseprocessor.h         baseprocessor.cpp
        tikhonovprocessor.h     tikhonovprocessor.cpp

        ${INCLUDE_DIRECTORIES}/qcustomplot.cpp
        ${INCLUDE_DIRECTORIES}/qcustomplot.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(
        ${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(
        ${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
