cmake_minimum_required(VERSION 4.0)
project(LABY2 C)

set(CMAKE_C_STANDARD 23)


add_compile_options(
        -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond
        -Wfloat-equal -Wshadow -Wconversion -Wjump-misses-init
        -Wlogical-not-parentheses -Wnull-dereference -Wvla -Werror
        -fstack-protector-strong -fsanitize=undefined -fno-sanitize-recover
        -g -fno-omit-frame-pointer -O1
)

add_executable(LABY2 main.c)


