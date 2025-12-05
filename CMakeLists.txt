cmake_minimum_required(VERSION 3.20)

project(Cpp2025)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
    src/main.cpp
    src/day1.cpp
    src/day2.cpp
    src/day3.cpp
    src/day4.cpp
    src/day5.cpp
)

add_executable(Cpp2025 ${SOURCE_FILES})
target_include_directories(Cpp2025 PUBLIC ${CMAKE_SOURCE_DIR}/include)
