cmake_minimum_required(VERSION 3.16)
project(FunQuizz VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  # Important!
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(FunQuizz
    main.cpp
    src/question/question.cpp
    src/repository/repository.cpp
    src/ui/mainwindow.cpp
    src/ui/managequestions.cpp
    src/ui/about.cpp
)

target_include_directories(FunQuizz PRIVATE
    src/question
    src/repository
    src/ui
)

target_link_libraries(FunQuizz PRIVATE Qt6::Core Qt6::Widgets)