cmake_minimum_required(VERSION 3.21)
project(2sem)

set(CMAKE_CXX_STANDARD 17)

add_executable(2sem main.cpp PersonTest.cpp PersonTest.h TestBase.cpp TestBase.h interpreter.cpp interpreter.h)
