cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(MainApp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXECUTABLE_SUFFIX ".out")

add_executable(MainApp 
    src/main.cpp
    )

add_subdirectory(../CommunicationLib build)
add_subdirectory(lib/position_detector)
add_subdirectory(lib/sensor)

target_link_libraries(MainApp PUBLIC 
    PositionDetector
    )
