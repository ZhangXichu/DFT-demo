cmake_minimum_required(VERSION 3.10)
project(ft_demo C)

set(CMAKE_C_STANDARD 99)

set(HEADER_DIR include)

set(SOURCES
    src/main.c
    src/dft.c
    src/complex.c
    src/matrix.c
    src/fft.c
    src/simple_rng.c
)

add_executable(ft_demo ${SOURCES})

include_directories(include)

target_link_libraries(ft_demo m) # link math.h to ft_demo