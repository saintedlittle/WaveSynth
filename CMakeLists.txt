cmake_minimum_required(VERSION 3.0)
project(wavGenerator C CXX)

set(CMAKE_C_STANDARD 23)

add_executable(wavGenerator
        src/main.c
        src/wav/make_wav.h src/wav/make_wav.c
        src/constants.h src/stb/stb_image.h)

if(MSVC)
    target_compile_options(wavGenerator PRIVATE /wd4244)
endif()