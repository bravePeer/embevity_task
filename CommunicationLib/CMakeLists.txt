cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(CommunicationLib STATIC
    src/server.cpp 
    src/client.cpp
    src/utils.cpp
    src/exceptions.cpp
    )

target_include_directories(CommunicationLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
