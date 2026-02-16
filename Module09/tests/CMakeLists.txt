cmake_minimum_required(VERSION 3.14)
project(Module09Tests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ex00 - BitcoinExchange
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../ex00/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..)
add_executable(TestModule09Ex00 TestModule09Ex00.cpp ../ex00/src/BitcoinExchange.cpp ../ex00/src/utils.cpp)
target_link_libraries(TestModule09Ex00 GTest::gtest_main)
target_include_directories(TestModule09Ex00 PRIVATE ../ex00/headers)

# ex01 - RPN
add_executable(TestModule09Ex01 TestModule09Ex01.cpp ../ex01/src/RPN.cpp ../ex01/src/utils.cpp)
target_link_libraries(TestModule09Ex01 GTest::gtest_main)
target_include_directories(TestModule09Ex01 PRIVATE ../ex01/headers)

# ex02 - PmergeMe (all code in .tpp, no separate .cpp needed)
add_executable(TestModule09Ex02 TestModule09Ex02.cpp)
target_link_libraries(TestModule09Ex02 GTest::gtest_main)
target_include_directories(TestModule09Ex02 PRIVATE ../ex02/headers)

include(GoogleTest)
gtest_discover_tests(TestModule09Ex00)
gtest_discover_tests(TestModule09Ex01)
gtest_discover_tests(TestModule09Ex02)
