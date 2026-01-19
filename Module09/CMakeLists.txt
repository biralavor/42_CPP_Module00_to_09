cmake_minimum_required(VERSION 3.10)
project(CPP_Module09 VERSION 1.0)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

enable_testing()
add_subdirectory(tests)

message(STATUS "Configuring tests for ${PROJECT_NAME}")
