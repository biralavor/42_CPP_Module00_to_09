cmake_minimum_required(VERSION 3.10)
project(CPP_Module05 VERSION 1.0)

# set project-wide properties
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# Enable testing for the whole project
enable_testing()

# Add exercise subdirectories
add_subdirectory(ex00)
add_subdirectory(ex01)
add_subdirectory(ex02)
add_subdirectory(ex03)

# Add tests directory
add_subdirectory(tests)

# Print test configuration
message(STATUS "Configuring tests for ${PROJECT_NAME}")
message(STATUS "Google Test will be used for unit testing")
