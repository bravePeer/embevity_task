cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(PositionDetector STATIC
    src/position_detector.cpp
    )

target_include_directories(PositionDetector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(PositionDetector PUBLIC 
    CommunicationLib    
    Sensor
    )