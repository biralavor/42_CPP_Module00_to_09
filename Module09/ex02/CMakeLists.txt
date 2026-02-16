set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(PmergeMe_lib INTERFACE)

target_include_directories(PmergeMe_lib INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(PmergeMe_main
	src/main.cpp
)

target_link_libraries(PmergeMe_main PRIVATE
	PmergeMe_lib
)
