cmake_minimum_required(VERSION 3.14)
project(Module01Tests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test for ex00 - Zombie
add_executable(
  TestModule01Ex00
  TestModule01Ex00.cpp
  ../ex00/src/Zombie.cpp
  ../ex00/src/newZombie.cpp
  ../ex00/src/randomChump.cpp
)
target_link_libraries(TestModule01Ex00 GTest::gtest_main)
target_include_directories(TestModule01Ex00 PRIVATE ../ex00/headers)

# Test for ex01 - ZombieHorde
add_executable(
  TestModule01Ex01
  TestModule01Ex01.cpp
  ../ex01/src/Zombie.cpp
  ../ex01/src/zombieHorde.cpp
)
target_link_libraries(TestModule01Ex01 GTest::gtest_main)
target_include_directories(TestModule01Ex01 PRIVATE ../ex01/headers)

# Test for ex03 - Weapon, HumanA, HumanB (References vs Pointers)
add_executable(
  TestModule01Ex03
  TestModule01Ex03.cpp
  ../ex03/src/Weapon.cpp
  ../ex03/src/HumanA.cpp
  ../ex03/src/HumanB.cpp
)
target_link_libraries(TestModule01Ex03 GTest::gtest_main)
target_include_directories(TestModule01Ex03 PRIVATE ../ex03/headers)

# Test for ex05 - Harl (Pointers to Member Functions)
add_executable(
  TestModule01Ex05
  TestModule01Ex05.cpp
  ../ex05/src/Harl.cpp
)
target_link_libraries(TestModule01Ex05 GTest::gtest_main)
target_include_directories(TestModule01Ex05 PRIVATE ../ex05/headers)

include(GoogleTest)
gtest_discover_tests(TestModule01Ex00)
gtest_discover_tests(TestModule01Ex01)
gtest_discover_tests(TestModule01Ex03)
gtest_discover_tests(TestModule01Ex05)
