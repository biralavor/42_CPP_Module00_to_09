cmake_minimum_required(VERSION 3.14)
project(Module04Tests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ex00 - Polymorphism
add_executable(TestModule04Ex00
  TestModule04Ex00.cpp
  ../ex00/src/Animal.cpp
  ../ex00/src/Dog.cpp
  ../ex00/src/Cat.cpp
  ../ex00/src/WrongAnimal.cpp
  ../ex00/src/WrongCat.cpp
  ../ex00/src/Utils.cpp
)
target_link_libraries(TestModule04Ex00 GTest::gtest_main)
target_include_directories(TestModule04Ex00 PRIVATE ../ex00/headers)

# ex01 - Deep Copy with Brain
add_executable(TestModule04Ex01
  TestModule04Ex01.cpp
  ../ex01/src/Animal.cpp
  ../ex01/src/Dog.cpp
  ../ex01/src/Cat.cpp
  ../ex01/src/Brain.cpp
  ../ex01/src/Utils.cpp
)
target_link_libraries(TestModule04Ex01 GTest::gtest_main)
target_include_directories(TestModule04Ex01 PRIVATE ../ex01/headers)

# ex02 - Abstract Class
add_executable(TestModule04Ex02
  TestModule04Ex02.cpp
  ../ex02/src/AAnimal.cpp
  ../ex02/src/Dog.cpp
  ../ex02/src/Cat.cpp
  ../ex02/src/Brain.cpp
  ../ex02/src/Utils.cpp
)
target_link_libraries(TestModule04Ex02 GTest::gtest_main)
target_include_directories(TestModule04Ex02 PRIVATE ../ex02/headers)

include(GoogleTest)
gtest_discover_tests(TestModule04Ex00)
gtest_discover_tests(TestModule04Ex01)
gtest_discover_tests(TestModule04Ex02)
