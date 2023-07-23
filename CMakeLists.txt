cmake_minimum_required(VERSION 3.0)
project(wavGenerator C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

add_executable(wavGenerator
        src/main.c
        src/wav/make_wav.h src/wav/make_wav.c
        src/bmp/process_wraper.cpp src/bmp/process_wraper.h
        src/cpp/process.h src/cpp/process.cpp src/cpp/bitmap_image.cpp)
