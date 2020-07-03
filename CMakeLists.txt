cmake_minimum_required(VERSION 3.10)
project(ft_demo)

set(CMAKE_CXX_STANDARD 14)

set(HEADER_DIR include)

set(SOURCES main.c dft.c complex.c matrix.c fft.c simple_rng.c)
set(HEADERS ${HEADER_DIR}/dft.h ${HEADER_DIR}/complex.h ${HEADER_DIR}/matrix.h ${HEADER_DIR}/config.h ${HEADER_DIR}/fft.h ${HEADER_DIR}/simple_rng.h)
set(EXECUTABLE ft_demo)

add_executable(${EXECUTABLE} ${HEADERS} ${SOURCES})

target_link_libraries(ft_demo m) # link math.h to ft_demo