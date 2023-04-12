cmake_minimum_required(VERSION 3.16)

project(DigitalWalletTracker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS -g)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(DigitalWalletTracker
    mainwindow.ui
    fsystem.cpp
    paymentwindow.cpp
    date.cpp
    displaywindow.cpp
    mainwindow.cpp
    main.cpp
)
target_link_libraries(DigitalWalletTracker PRIVATE
    Qt6::Widgets)

set_target_properties(DigitalWalletTracker PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)