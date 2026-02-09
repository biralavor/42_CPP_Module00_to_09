set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(MutantStack_lib INTERFACE)

target_include_directories(MutantStack_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(mutantstack
	src/main.cpp
)

target_link_libraries(mutantstack PRIVATE
	MutantStack_lib
)
