cmake_minimum_required (VERSION 2.6)
project(zadanie_2_multithread_proga C)
set(CMAKE_C_STANDARD 11)
add_executable(zadanie_2_multithread_proga libstatic.c libstatic.h main.c libdynamic.c libdynamic.h)
