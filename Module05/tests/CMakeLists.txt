cmake_minimum_required(VERSION 3.14)
project(Module05Tests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ex00 - Bureaucrat with exceptions
add_executable(TestModule05Ex00
  TestModule05Ex00.cpp
  ../ex00/src/Bureaucrat.cpp
)
target_link_libraries(TestModule05Ex00 GTest::gtest_main)
target_include_directories(TestModule05Ex00 PRIVATE ../ex00/headers)

# ex01 - Bureaucrat + Form
add_executable(TestModule05Ex01
  TestModule05Ex01.cpp
  ../ex01/src/Bureaucrat.cpp
  ../ex01/src/Form.cpp
)
target_link_libraries(TestModule05Ex01 GTest::gtest_main)
target_include_directories(TestModule05Ex01 PRIVATE ../ex01/headers)

# ex02 - AForm + concrete forms
add_executable(TestModule05Ex02
  TestModule05Ex02.cpp
  ../ex02/src/Bureaucrat.cpp
  ../ex02/src/AForm.cpp
  ../ex02/src/ShrubberyCreationForm.cpp
  ../ex02/src/RobotomyRequestForm.cpp
  ../ex02/src/PresidentialPardonForm.cpp
)
target_link_libraries(TestModule05Ex02 GTest::gtest_main)
target_include_directories(TestModule05Ex02 PRIVATE ../ex02/headers)

# ex03 - Intern
add_executable(TestModule05Ex03
  TestModule05Ex03.cpp
  ../ex03/src/Bureaucrat.cpp
  ../ex03/src/AForm.cpp
  ../ex03/src/ShrubberyCreationForm.cpp
  ../ex03/src/RobotomyRequestForm.cpp
  ../ex03/src/PresidentialPardonForm.cpp
  ../ex03/src/Intern.cpp
)
target_link_libraries(TestModule05Ex03 GTest::gtest_main)
target_include_directories(TestModule05Ex03 PRIVATE ../ex03/headers)

include(GoogleTest)
gtest_discover_tests(TestModule05Ex00)
gtest_discover_tests(TestModule05Ex01)
gtest_discover_tests(TestModule05Ex02)
gtest_discover_tests(TestModule05Ex03)
