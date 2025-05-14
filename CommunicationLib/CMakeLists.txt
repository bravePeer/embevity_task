cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(HEADER_FOLDER include)

# target_include_directories(CommunicationLib PRIVATE ${HEADER_FOLDER})
# include_directories(${HEADER_FOLDER})
include_directories(include)

add_library(CommunicationLib 
    src/server.cpp 
    include/server.hpp
    src/client.cpp
    include/client.hpp
    include/special_commands.hpp
    include/utils.hpp
    src/utils.cpp
    )
