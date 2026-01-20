set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Serializer_lib
    src/Serializer.cpp
    src/Data.cpp
)

target_include_directories(Serializer_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(serializer
    src/main.cpp
)

target_link_libraries(serializer PRIVATE
    Serializer_lib
)