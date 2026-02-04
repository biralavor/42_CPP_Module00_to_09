cmake_minimum_required(VERSION 3.14)
project(Module08Tests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ex00 - easyfind (header-only template)
add_executable(TestModule08Ex00 TestModule08Ex00.cpp)
target_link_libraries(TestModule08Ex00 GTest::gtest_main)
target_include_directories(TestModule08Ex00 PRIVATE ../ex00)

# ex01 - Span class
add_executable(TestModule08Ex01 TestModule08Ex01.cpp ../ex01/src/Span.cpp)
target_link_libraries(TestModule08Ex01 GTest::gtest_main)
target_include_directories(TestModule08Ex01 PRIVATE ../ex01/headers)

# ex02 - MutantStack (header-only template)
# add_executable(TestModule08Ex02 TestModule08Ex02.cpp)
# target_link_libraries(TestModule08Ex02 GTest::gtest_main)
# target_include_directories(TestModule08Ex02 PRIVATE ../ex02)

include(GoogleTest)
gtest_discover_tests(TestModule08Ex00)
gtest_discover_tests(TestModule08Ex01)
# gtest_discover_tests(TestModule08Ex02)
