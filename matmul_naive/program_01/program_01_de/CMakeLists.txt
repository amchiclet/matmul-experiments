cmake_minimum_required(VERSION 3.16)
project(matmul_naive)
add_executable(wrapper_naive core.c wrapper.c main.c measure.c)
target_compile_options(wrapper_naive PRIVATE -std=c99)
target_link_libraries(wrapper_naive pthread m dl)
