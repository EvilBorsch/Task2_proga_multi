project(zadanie_2_multithread_proga C)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu99 -pthread")

add_executable(zadanie_2_multithread_proga libstatic.c libstatic.h main.c libdynamic.c libdynamic.h)
