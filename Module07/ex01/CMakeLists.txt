set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Iter_lib
	src/Iter.cpp
)

target_include_directories(Iter_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(iter
	src/main.cpp
)

target_link_libraries(iter PRIVATE
	Iter_lib
)
