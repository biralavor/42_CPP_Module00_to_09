set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Bureaucrat_lib
	src/Bureaucrat.cpp
)

target_include_directories(Bureaucrat_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(bureaucrat
	src/main.cpp
)

target_link_libraries(bureaucrat PRIVATE
	Bureaucrat_lib
)
