cmake_minimum_required(VERSION 3.10)
# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Simulator)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXECUTABLE_SUFFIX ".out")

add_executable(Simulator 
    src/main.cpp
    src/BM1390GLV_ZTR.cpp
    include/BM1390GLV_ZTR.hpp
    include/memory_map.hpp
    )

add_subdirectory(../CommunicationLib build)
target_link_libraries(Simulator PUBLIC CommunicationLib)
target_include_directories(Simulator PUBLIC "include" "../CommunicationLib/include")