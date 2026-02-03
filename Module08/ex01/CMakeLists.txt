set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Span_lib
	src/Span.cpp
)

target_include_directories(Span_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(span
	src/main.cpp
)

target_link_libraries(span PRIVATE
	Span_lib
)
