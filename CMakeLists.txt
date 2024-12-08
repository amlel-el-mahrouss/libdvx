cmake_minimum_required(VERSION 3.16)

project(DVX LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DVX SHARED
    inc/dvx_stream.h
    inc/libdvx_global.h
    src/dvx_core_api.cpp
    inc/dvx_core_api.h
    src/dvx_stream.cpp
    src/dvx_platform_tq.cpp
)

target_link_libraries(DVX SDL2)
