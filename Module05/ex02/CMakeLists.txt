set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Aform_lib
	src/Bureaucrat.cpp
	src/AForm.cpp
	src/PresidentialPardonForm.cpp
	src/RobotomyRequestForm.cpp
	src/ShrubberyCreationForm
)

target_include_directories(Aform_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(aform
	src/main.cpp
)

target_link_libraries(aform PRIVATE
	Aform_lib
)
