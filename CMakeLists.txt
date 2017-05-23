cmake_minimum_required(VERSION 3.6)
project(lem-in)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        lem-in.c lem-in.h)

add_executable(lem-in ${SOURCE_FILES})