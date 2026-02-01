set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Easyfind_lib
	src/Easyfind.cpp
)

target_include_directories(Easyfind_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(easyfind
	src/main.cpp
)

target_link_libraries(easyfind PRIVATE
	Easyfind_lib
)
