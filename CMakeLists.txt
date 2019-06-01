cmake_minimum_required(VERSION 3.14)
project(tp_cripto)

set(CMAKE_CXX_STANDARD 14)

add_executable(tp_cripto main.c main.h random.c random.h image_manipulation.c image_manipulation.h)
