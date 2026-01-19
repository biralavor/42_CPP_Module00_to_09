cmake_minimum_required(VERSION 3.14)
project(Module02Tests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test for ex00 - Fixed (Orthodox Canonical Form)
add_executable(
  TestModule02Ex00
  TestModule02Ex00.cpp
  ../ex00/src/Fixed.cpp
)
target_link_libraries(TestModule02Ex00 GTest::gtest_main)
target_include_directories(TestModule02Ex00 PRIVATE ../ex00/headers)

# Test for ex01 - Fixed with conversions
add_executable(
  TestModule02Ex01
  TestModule02Ex01.cpp
  ../ex01/src/Fixed.cpp
)
target_link_libraries(TestModule02Ex01 GTest::gtest_main)
target_include_directories(TestModule02Ex01 PRIVATE ../ex01/headers)

# Test for ex02 - Fixed with operators
add_executable(
  TestModule02Ex02
  TestModule02Ex02.cpp
  ../ex02/src/Fixed.cpp
)
target_link_libraries(TestModule02Ex02 GTest::gtest_main)
target_include_directories(TestModule02Ex02 PRIVATE ../ex02/headers)

include(GoogleTest)
gtest_discover_tests(TestModule02Ex00)
gtest_discover_tests(TestModule02Ex01)
gtest_discover_tests(TestModule02Ex02)
