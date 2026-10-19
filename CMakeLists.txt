cmake_minimum_required(VERSION 3.16)
project(lab01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

option(ENABLE_SANITIZERS "Build with AddressSanitizer and UBSan" OFF)
if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

add_library(matrix_ops STATIC src/matrix_ops.cpp)
target_include_directories(matrix_ops PUBLIC include)
target_compile_options(matrix_ops PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab01 src/main.cpp)
target_link_libraries(lab01 PRIVATE matrix_ops)
target_compile_options(lab01 PRIVATE -Wall -Wextra -Wpedantic)

include(FetchContent)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_variant tests/test_variant.cpp)
target_link_libraries(test_variant PRIVATE matrix_ops GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_variant)
