cmake_minimum_required(VERSION 3.13)
project(tp_cripto)

set(CMAKE_CXX_STANDARD 14)

add_executable(tp_cripto main.c include/main.h random.c include/random.h image_manipulation.c include/image_manipulation.h matrices.c tests/image_manipulation_test.c tests/image_manipulation_test.h tests/main_test.c tests/main_test.h tests/util.c tests/util.h)