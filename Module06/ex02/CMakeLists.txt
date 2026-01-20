set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Base_lib
    src/Base.cpp
)

target_include_directories(Base_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(base
    src/main.cpp
)

target_link_libraries(base PRIVATE
    Base_lib
)
