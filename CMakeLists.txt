#cmake_minimum_required(VERSION 3.13)
project(tp_cripto)

set(CMAKE_CXX_STANDARD 14)

add_executable(tp_cripto main.c include/main.h random.c include/random.h image_manipulation.c include/image_manipulation.h matrices.c include/matrices.h tests/image_manipulation_test.c tests/image_manipulation_test.h tests/main_test.c tests/main_test.h tests/util.c tests/util.h tests/azzahra_test.c tests/azzahra_test.h azzahra.c include/azzahra.h tests/steganography_test.c tests/steganography_test.h steganography.c include/steganography.h tests/matrices_test.h tests/matrices_test.c include/Gmatrices.h GMatrices.c utils.c include/utils.h)
target_link_libraries(tp_cripto m)
