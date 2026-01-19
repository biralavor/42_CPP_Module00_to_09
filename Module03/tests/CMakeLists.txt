cmake_minimum_required(VERSION 3.14)
project(Module03Tests)

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

# Test for ex00 - ClapTrap (Base Class)
add_executable(
  TestModule03Ex00
  TestModule03Ex00.cpp
  ../ex00/src/ClapTrap.cpp
  ../ex00/src/Utils.cpp
)
target_link_libraries(TestModule03Ex00 GTest::gtest_main)
target_include_directories(TestModule03Ex00 PRIVATE ../ex00/headers)

# Test for ex01 - ScavTrap (Derived Class)
add_executable(
  TestModule03Ex01
  TestModule03Ex01.cpp
  ../ex01/src/ClapTrap.cpp
  ../ex01/src/ScavTrap.cpp
  ../ex01/src/Utils.cpp
)
target_link_libraries(TestModule03Ex01 GTest::gtest_main)
target_include_directories(TestModule03Ex01 PRIVATE ../ex01/headers)

# Test for ex02 - FragTrap (Another Derived Class)
add_executable(
  TestModule03Ex02
  TestModule03Ex02.cpp
  ../ex02/src/ClapTrap.cpp
  ../ex02/src/ScavTrap.cpp
  ../ex02/src/FragTrap.cpp
  ../ex02/src/Utils.cpp
)
target_link_libraries(TestModule03Ex02 GTest::gtest_main)
target_include_directories(TestModule03Ex02 PRIVATE ../ex02/headers)

include(GoogleTest)
gtest_discover_tests(TestModule03Ex00)
gtest_discover_tests(TestModule03Ex01)
gtest_discover_tests(TestModule03Ex02)
