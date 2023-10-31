cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME NMR_Processing)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(INCLUDE_DIRECTORIES dependencies/QCustomPlot)
set(WIDGET_DIRECTORY widgets)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set(VCPKG_TARGET_TRIPLET x64-windows-static)
set(CMAKE_TOOLCHAIN_FILE D:/Development/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
include(${CMAKE_TOOLCHAIN_FILE})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS PrintSupport Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport Widgets REQUIRED)
find_package(OpenMP)


set(BLA_VENDOR OpenBLAS)
set(CMAKE_C_FLAGS -fopenmp)
find_package(BLAS REQUIRED)
find_package(OpenBLAS REQUIRED)
set(ENV{OPENBLAS_NUM_THREADS}, 8)
include_directories(${BLAS_INCLUDE_DIRS})
find_package(Armadillo REQUIRED)
find_package(NLopt CONFIG REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        ${WIDGET_DIRECTORY}/mainwindow.h                ${WIDGET_DIRECTORY}/mainwindow.cpp
        ${WIDGET_DIRECTORY}/plotwidget.h                ${WIDGET_DIRECTORY}/plotwidget.cpp
        ${WIDGET_DIRECTORY}/processwidget.h             ${WIDGET_DIRECTORY}/processwidget.cpp
        ${WIDGET_DIRECTORY}/baseprocesswidget.h         ${WIDGET_DIRECTORY}/baseprocesswidget.cpp
        ${WIDGET_DIRECTORY}/tikhonovprocesswidget.h     ${WIDGET_DIRECTORY}/tikhonovprocesswidget.cpp
        ${WIDGET_DIRECTORY}/sequentalprocesswidget.h    ${WIDGET_DIRECTORY}/sequentalprocesswidget.cpp
        ${WIDGET_DIRECTORY}/filesystemwidget.h          ${WIDGET_DIRECTORY}/filesystemwidget.cpp
        ${WIDGET_DIRECTORY}/logwidget.h                 ${WIDGET_DIRECTORY}/logwidget.cpp

        ${WIDGET_DIRECTORY}/subwidgets/customplotzoom.h ${WIDGET_DIRECTORY}/subwidgets/customplotzoom.cpp

        baseprocessor.h         baseprocessor.cpp
        tikhonovprocessor.h     tikhonovprocessor.cpp
        sequentalprocessor.h    sequentalprocessor.cpp

        mathfunctions.h         mathfunctions.cpp
        approximation.h         approximation.cpp

        nmrdata.h               nmrdata.cpp
        nmrdatastruct.h

        ${INCLUDE_DIRECTORIES}/qcustomplot.cpp
        ${INCLUDE_DIRECTORIES}/qcustomplot.h
)

#option(option(X_VCPKG_APPLOCAL_DEPS_INSTALL ON))

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

target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIRECTORIES}
    ${ARMADILLO_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::PrintSupport

    ${BLAS_LIBRARIES}
    OpenBLAS::OpenBLAS
    ${ARMADILLO_LIBRARIES}
    NLopt::nlopt
)

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
