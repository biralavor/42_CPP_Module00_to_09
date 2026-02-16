set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(RPN_lib
	src/RPN.cpp
	src/utils.cpp
)

target_include_directories(RPN_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(RPN_main
	src/main.cpp
)

target_link_libraries(RPN_main PRIVATE
	RPN_lib
)
