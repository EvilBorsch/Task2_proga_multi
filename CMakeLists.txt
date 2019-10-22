project(zadanie_2_multithread_proga C)

set(CMAKE_C_STANDARD 11)

add_executable(zadanie_2_multithread_proga pthread.h libstatic.c libstatic.h main.c libdynamic.c libdynamic.h)
