# C++ list Modules (0 to 9) from 42 school - 42 São Paulo campus

<table border="0" align="center">
  <tr>
    <td width="33%" align="left" valign="center">
      <img src="https://github.com/user-attachments/assets/04a63315-559b-4bc3-a222-ce8323b7baee" width="100%" alt="CPP Progress">
    </td>
    <td width="35%" valign="top">
      <br>
      <img src="https://img.shields.io/badge/Module%2000-100%25-brightgreen"><br>
      <img src="https://img.shields.io/badge/Module%2001-100%25-brightgreen"><br>
      <img src="https://img.shields.io/badge/Module%2002-80%25-yellow"><br>
      <img src="https://img.shields.io/badge/Module%2003-80%25-yellow"><br>
      <img src="https://img.shields.io/badge/Module%2004-80%25-yellow">
    </td>
    <td width="35%" valign="top">
      <br>
      <img src="https://img.shields.io/badge/Module%2005-100%25-brightgreen"><br>
      <img src="https://img.shields.io/badge/Module%2006-100%25-brightgreen"><br>
      <img src="https://img.shields.io/badge/Module%2007-100%25-brightgreen"><br>
      <img src="https://img.shields.io/badge/Module%2008-Pending-lightgrey"><br>
      <img src="https://img.shields.io/badge/Module%2009-Pending-lightgrey">
    </td>
  </tr>
</table>



> [!Important]
> - Module 00 -> basics about Namespaces, classes, member functions, stdio streams, initialization lists, static, const, and some other basic stuff
> - Module 01 -> foundations about Memory allocation, pointers to members, references and switch statements
> - Module 02 -> training Ad-hoc polymorphism, operator overloading and the Orthodox Canonical class form
> - Module 03 -> weird Inheritance, lol
> - Module 04 -> more Subtype Polymorphism, Abstract Classes, and Interfaces
> - Module 05 -> Repetition and Exceptions
> - Module 06 -> C++ casts (static_cast<>, dynamic_cast<>, const_cast<>, reinterpret_cast<>)
> - Module 07 -> C++ templates
> - Module 08 -> Templated containers (vector, map, stack, etc), iterators, algorithms
> - Module 09 -> STL (Standard Template Library) algorithms and function objects
https://cplusplus.com/doc/tutorial

https://www.learncpp.com/

> [!NOTE]
> This project has a few tests with Google Tests <br>
> ![image](https://github.com/user-attachments/assets/8b234810-9a88-4903-97ab-0ea2f906fb32)


## Makefile Targets

A set of convenient Makefile targets is provided to help you work with Docker and development tasks in this project:

| Target         | Description                                                                                   |
|----------------|----------------------------------------------------------------------------------------------|
| **build**      | Build and start the Docker container in detached mode.                                        |
| **go**         | Build/start the container, run preparations, then open an interactive shell in the app.       |
| **stop**       | Stop the running Docker container.                                                            |
| **down**       | Stop and remove the Docker container and associated resources.                                |
| **reload-docker** | Stop, rebuild, and restart the Docker container.                                             |
| **ps**         | List all Docker containers.                                                                   |
| **deep-clean** | Clean up unused Docker builder cache (frees disk space).                                      |

### Usage

To run any of these tasks, use:

```sh
make <target>
```

## Module Makefile Targets

Each module (Module00-Module09) has a consistent set of Makefile targets:

| Target         | Description                                    |
|----------------|------------------------------------------------|
| **make**       | Build exercises + run all tests                |
| **make test**  | Run all tests (Google Test)                    |
| **make test-exNN** | Run tests for specific exercise (e.g., `make test-ex00`) |
| **make build_cmake** | Build with CMake system                   |
| **make build_exercises** | Build individual exercises only        |
| **make build_all** | Build with both systems                    |
| **make clean** | Clean both build systems                       |
| **make fclean**| Deep clean both systems                        |
| **make re**    | Full rebuild                                   |
| **make help**  | Show all available targets                     |

### Per-Module Usage

```bash
# Run all tests for a module
cd Module06 && make test

# Run specific exercise tests
cd Module06 && make test-ex01

# Build and run a specific exercise
cd Module06/ex00 && make go
