cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Sensor STATIC
    src/sensor.cpp
    )

target_include_directories(Sensor PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(Sensor PUBLIC 
    CommunicationLib
    )