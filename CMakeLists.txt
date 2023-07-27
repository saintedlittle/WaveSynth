cmake_minimum_required(VERSION 3.0)
project(wavGenerator C CXX)

set(CMAKE_C_STANDARD 23)

add_executable(wavGenerator
        src/main.c
        src/wav/make_wav.h src/wav/make_wav.c
        src/constants.h src/stb/stb_image.h src/math/functions.h src/math/functions.c src/noise/noises.h src/noise/noises.c src/waves/waves.h src/waves/waves.c src/utils/utils.h src/math/big_double.h src/math/big_double.c src/math/big_double.h)

if(MSVC)
    target_compile_options(wavGenerator PRIVATE /wd4244)
else()
    target_link_libraries(wavGenerator PRIVATE m)
endif()