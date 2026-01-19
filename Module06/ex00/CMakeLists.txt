set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(ScalarConverter_lib
	src/ScalarConverter.cpp
)

target_include_directories(ScalarConverter_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(scalar_converter
	src/main.cpp
)

target_link_libraries(scalar_converter PRIVATE
	ScalarConverter_lib
)
