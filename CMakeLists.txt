cmake_minimum_required(VERSION 3.16)

project(DVX.wasm LANGUAGES CXX)

set(CMAKE_C_COMPILER emcc)
set(CMAKE_CXX_COMPILER emcc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DVX.wasm
    inc/dvx_core_api.h
    inc/dvx_stream.h
    inc/libdvx_global.h
    src/dvx_core_api.cpp
    src/dvx_stream.cpp
    src/dvx_main.cpp
    src/dvx_platform_tq.cpp
)

include_directories(DVX.asm BEFORE inc/)
