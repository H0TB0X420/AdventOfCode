cmake_minimum_required(VERSION 3.20)

project(Cpp2025)

set(SOURCE_FILES
    src/main.cpp
    src/day1.cpp
    src/day2.cpp
    src/day3.cpp
    src/day4.cpp
    src/day5.cpp
    src/day6.cpp
    src/day7.cpp
)

add_executable(Cpp2025 ${SOURCE_FILES})

# Force the standard on the target specifically
target_compile_features(Cpp2025 PUBLIC cxx_std_20)

# Enforce that if the compiler doesn't support C++20, CMake should fail config
set_target_properties(Cpp2025 PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO # distinct from GNU extensions, keeps it strict standard
)

target_include_directories(Cpp2025 PUBLIC ${CMAKE_SOURCE_DIR}/include)