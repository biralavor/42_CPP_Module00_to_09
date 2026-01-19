set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Intern_lib
	src/Bureaucrat.cpp
	src/AForm.cpp
	src/PresidentialPardonForm.cpp
	src/RobotomyRequestForm.cpp
	src/ShrubberyCreationForm
	Intern.cpp
)

target_include_directories(Intern_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(intern-coffee-making
	src/main.cpp
)

target_link_libraries(intern PRIVATE
	Intern_lib
)