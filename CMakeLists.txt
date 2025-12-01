cmake_minimum_required(VERSION 3.20)

project(Cpp2025)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. Best practice: List files explicitly to ensure CMake detects changes.
# 2. Fixed typo: SOURCE_FIlES -> SOURCE_FILES
set(SOURCE_FILES
    src/main.cpp
    src/Day1/day1.cpp
)

add_executable(Cpp2025 ${SOURCE_FILES})

# 3. Modern CMake uses target_include_directories instead of global include_directories
# Pointing to 'include' allows you to write #include "Day1/day1.h" in your code
target_include_directories(Cpp2025 PUBLIC ${CMAKE_SOURCE_DIR}/include)
