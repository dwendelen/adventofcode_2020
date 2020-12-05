cmake_minimum_required(VERSION 3.17)
project(adventofcode_2020)

set(CMAKE_CXX_STANDARD 14)

add_executable(day01_a day01/day01_a/main.cpp util.cpp)
add_executable(day01_b day01/day01_b/main.cpp util.cpp)

add_executable(day02_a day02/day02_a/main.cpp util.cpp)
add_executable(day02_b day02/day02_b/main.cpp util.cpp)

add_executable(day03_a day03/day03_a/main.cpp util.cpp)
add_executable(day03_b day03/day03_b/main.cpp util.cpp)

add_executable(day04_a day04/day04_a/main.cpp util.cpp)
add_executable(day04_b day04/day04_b/main.cpp util.cpp)
