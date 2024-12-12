# CMakeLists for Sha1 module
#
# © 2024 by Hatem Nabli

cmake_minimum_required(VERSION 3.8)
set(this Sha1)

set(Headers 
    include/Sha1/Sha1.hpp
)

set(Sources 
    src/Sha1.cpp
)

add_library(${this} STATIC ${Headers} ${Sources})
set_target_properties(${this} PROPERTIES 
    FOLDER Libraries
)

target_include_directories(${this} PUBLIC include)

add_subdirectory(test)