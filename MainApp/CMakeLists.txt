cmake_minimum_required(VERSION 3.10)
# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(MainApp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXECUTABLE_SUFFIX ".out")

add_executable(MainApp src/main.cpp)
add_subdirectory(../CommunicationLib build)
target_link_libraries(MainApp PUBLIC CommunicationLib)
target_include_directories(MainApp PUBLIC "include" "../CommunicationLib/include")