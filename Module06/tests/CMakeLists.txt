cmake_minimum_required(VERSION 3.10)
project(Module06Tests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# Set policy to handle FetchContent timestamps
# cmake_policy(SET CMP0135 NEW)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test for ex00 - ScalarConverter
add_executable(
  TestModule06Ex00
  TestModule06Ex00.cpp
  ../ex00/src/ScalarConverter.cpp
)
target_link_libraries(TestModule06Ex00 GTest::gtest_main)
target_include_directories(TestModule06Ex00 PRIVATE ../ex00/headers)

# Test for ex01 - Serializer
add_executable(
  TestModule06Ex01
  TestModule06Ex01.cpp
  ../ex01/src/Serializer.cpp
  ../ex01/src/Data.cpp
)
target_link_libraries(TestModule06Ex01 GTest::gtest_main)
target_include_directories(TestModule06Ex01 PRIVATE ../ex01/headers)

# Test for ex02 - Type Identification
add_executable(
  TestModule06Ex02
  TestModule06Ex02.cpp
  ../ex02/src/Base.cpp
)
target_link_libraries(TestModule06Ex02 GTest::gtest_main)
target_include_directories(TestModule06Ex02 PRIVATE ../ex02/headers)

include(GoogleTest)
gtest_discover_tests(TestModule06Ex00)
gtest_discover_tests(TestModule06Ex01)
gtest_discover_tests(TestModule06Ex02)
