cmake_minimum_required(VERSION 3.24)
project(owm-api VERSION 2.0.0 LANGUAGES CXX)

message(STATUS "Building Project: ${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -rdynamic)
set(CMAKE_CXX_FLAGS -g3)
set(CMAKE_CXX_FLAGS -Wall)      # enable most warning
set(CMAKE_CXX_FLAGS -Wextra)    # enable extra warnings
add_compile_options(-Wall)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Network Core REQUIRED)

set(EXEC_NAME ${PROJECT_NAME})
add_executable(${EXEC_NAME})

add_subdirectory(src)

target_link_libraries(${EXEC_NAME} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)
