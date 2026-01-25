set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Array_lib
	src/Array.cpp
)

target_include_directories(Array_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(array
	src/main.cpp
)

target_link_libraries(array PRIVATE
	Array_lib
)
