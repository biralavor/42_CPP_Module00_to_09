set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Whatever_lib
	src/Whatever.cpp
)

target_include_directories(Whatever_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(whatever
	src/main.cpp
)

target_link_libraries(whatever PRIVATE
	Whatever_lib
)
