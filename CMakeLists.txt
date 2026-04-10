cmake_minimum_required(VERSION 3.16)

project(BankingManagementSystem_Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Added 'Sql' to the components list
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        database.h    # Moved inside the source list for better organization
        database.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BankingManagementSystem_Project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        styling.qss
        bank.h bank.cpp
        loginwindow.h loginwindow.cpp
        signupwindow.h signupwindow.cpp
        dashboardwindow.h dashboardwindow.cpp
        basepage.h basepage.cpp
        resources.qrc
    )
else()
    if(ANDROID)
        add_library(BankingManagementSystem_Project SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(BankingManagementSystem_Project
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 2. Link the Sql library here
target_link_libraries(BankingManagementSystem_Project PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BankingManagementSystem_Project)
endif()

set_target_properties(BankingManagementSystem_Project PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    # Note: I'm leaving WIN32_EXECUTABLE TRUE, but if you want to see console
    # output (qDebug), change this to FALSE during debugging.
    WIN32_EXECUTABLE FALSE
)

include(GNUInstallDirs)
install(TARGETS BankingManagementSystem_Project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BankingManagementSystem_Project)
endif()
