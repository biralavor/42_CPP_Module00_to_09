set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Form_lib
    src/Bureaucrat.cpp
    src/Form.cpp
)

target_include_directories(Form_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(form
    src/main.cpp
)

target_link_libraries(form PRIVATE
    Form_lib
)
