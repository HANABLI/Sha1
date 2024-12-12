# CMakeLists for Sha1Tests Module
#
# © 2024 by Hatem Nabli

cmake_minimum_required(VERSION 3.8)

set(this Sha1Tests)

option(SHA1_TESTS_LONG_TEST_VECTOR "Include insane long test vector (it takes more than 20 seconds)" ON)

set(Sources src/Sha1Tests.cpp)

add_executable(${this} ${Sources})
set_target_properties(${this} PROPERTIES 
    FOLDER Tests
)

if(SHA1_TESTS_LONG_TEST_VECTOR)
    target_compile_definitions(${this} PRIVATE INCLUDE_SHA1_TEST_LONG_VECTOR)
endif(SHA1_TESTS_LONG_TEST_VECTOR)

target_include_directories(${this} PRIVATE ..)

target_link_libraries(${this} PUBLIC
    gtest_main
    Sha1
)
