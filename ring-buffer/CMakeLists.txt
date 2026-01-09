cmake_minimum_required(VERSION 3.14)
project(RingBufferTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests ring_buffer_test.cpp)
target_link_libraries(run_tests gtest_main)

target_include_directories(run_tests PRIVATE .)