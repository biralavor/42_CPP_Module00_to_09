cmake_minimum_required(VERSION 3.14)
project(Module07Tests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test for ex00 - Function Templates (swap, min, max)
# Note: ex00 is header-only, no .cpp files needed
add_executable(
  TestModule07Ex00
  TestModule07Ex00.cpp
)
target_link_libraries(TestModule07Ex00 GTest::gtest_main)
target_include_directories(TestModule07Ex00 PRIVATE ../ex00)

# Test for ex01 - iter Function Template
# Note: ex01 is header-only, no .cpp files needed
add_executable(
  TestModule07Ex01
  TestModule07Ex01.cpp
)
target_link_libraries(TestModule07Ex01 GTest::gtest_main)
target_include_directories(TestModule07Ex01 PRIVATE ../ex01)

# Test for ex02 - Array Class Template
# Note: ex02 is header-only (template class), no .cpp files needed
add_executable(
  TestModule07Ex02
  TestModule07Ex02.cpp
)
target_link_libraries(TestModule07Ex02 GTest::gtest_main)
target_include_directories(TestModule07Ex02 PRIVATE ../ex02)

include(GoogleTest)
gtest_discover_tests(TestModule07Ex00)
gtest_discover_tests(TestModule07Ex01)
gtest_discover_tests(TestModule07Ex02)
