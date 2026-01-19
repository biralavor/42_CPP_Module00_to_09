## 42 C++ Modules
This repository contains solutions to the 42 C++ Modules (00-09). Each module has specific requirements and constraints, so refer to the module instructions for details.
C++ is a general-purpose programming language created by Bjarne Stroustrup as an extension of the C programming language, or "C with Classes" (source: Wikipedia).
The goal of these modules is to introduce I to Object-Oriented Programming.
This will be the starting point of the C++ journey. Many languages are recommended for learning OOP. We decided to choose C++ since it’s derived from the old friend C. Since C++ is a complex language, and in order to keep things simple, the code will follow the C++98 standard.
We are aware modern C++ is way different in a lot of aspects. So if I want to become a proficient C++ developer, it’s up to I to go further after the 42 Common
Core! I will discover new concepts step-by-step. The exercises will progressively increase in complexity.

## General Rules
### Compiling
- Compile the code with c++ and the flags -Wall -Wextra -Werror
- The code should still compile if I add the flag -std=c++98 Formatting and naming conventions
- The exercise directories will be named this way: ex00, ex01, ..., exn
- Name the files, classes, functions, member functions and attributes as required in the guidelines.
- Write class names in UpperCamelCase format. Files containing class code will always be named according to the class name. For instance: ClassName.hpp/ClassName.h, ClassName.cpp, or ClassName.tpp. Then, if I have a header file containing the definition of a class "BrickWall" standing for a brick wall, its name will be BrickWall.hpp.
- Unless specified otherwise, every output message must end with a newline character and be displayed to the standard output.
- Goodbye Norminette! No coding style is enforced in the C++ modules. I can follow the favorite one. But keep in mind that code the peer evaluators can’t understand is code they can’t grade. Do the best to write clean and readable code. 
### Allowed/Forbidden
I are not coding in C anymore. Time to C++! Therefore:
- I are allowed to use almost everything from the standard library. Thus, instead of sticking to what I already know, it would be smart to use the C++-ish versions of the C functions I are used to as much as possible.
- However, I can’t use any other external library. It means C++11 (and derived forms) and Boost libraries are forbidden. The following functions are forbidden too: *printf(), *alloc() and free(). If I use them, the grade will be 0 and that’s it.
- Note that unless explicitly stated otherwise, the using namespace <ns_name> and friend keywords are forbidden. Otherwise, the grade will be -42.
- I are allowed to use the STL only in Modules 08 and 09. That means: no Containers (vector/list/map, and so forth) and no Algorithms (anything that requires including the <algorithm> header) until then. Otherwise, the grade will be -42.
### A few design requirements
- Memory leakage occurs in C++ too. When I allocate memory (by using the new keyword), I must avoid memory leaks.
- From Module 02 to Module 09, the classes must be designed in the Orthodox Canonical Form, except when explicitly stated otherwise.
- Any function implementation put in a header file (except for function templates) means 0 to the exercise.
- I should be able to use each of the headers independently from others. Thus, they must include all the dependencies they need. However, I must avoid the problem of double inclusion by adding include guards. Otherwise, the grade will be 0. I can add some additional files if I need to (i.e., to split the code). As these assignments are not verified by a program, feel free to do so as long as I turn in the mandatory files.
- Sometimes, the guidelines of an exercise look short but the examples can show requirements that are not explicitly written in the instructions.


### Module 00 - Namespaces, classes, member functions, stdio streams, initialization lists, static, const, and some other basic stuff -> [42-cpp-module00-en.subject.pdf](42-cpp-module00-en.subject.pdf)
Basic C++ syntax, compilation, and Makefiles. Namespaces, classes, member functions, stdio streams, initialization lists, static, const, and some other basic stuff
### Exercise 00: Megaphone
Just to make sure that everybody is awake, write a program that takes a string as an argument and displays it in uppercase followed by a newline. If no argument is provided, display "LOUD AND UNBEARABLE FEEDBACK NOISE" followed by a newline.
### Exercise 01: My Awesome PhoneBook.
Create a simple phonebook application that allows users to add, search, and display contacts. Each contact should have a name, phone number, and email address. 8 contacts in an array, without dinamic memory allocation. The Phonebook has 3 commands: ADD, SEARCH and EXIT.
### Exercise 02: The Job Of The Dreams
I should recreate the Accountrs.cpp file, based on Accounts.hpp provided. The program will simulate a bank account system, where I can create accounts, make deposits, and withdraw money. The program should keep track of the total number of accounts, total amount of money across all accounts, total number of deposits, and total number of withdrawals.


## Module 01 - Memory allocation, pointers to members, references and switch statements -> [42-cpp-module01-en.subject.pdf](42-cpp-module01-en.subject.pdf)
Memory allocation, pointers to members, references and switch statements.
### Exercise 00: Braiiiiiiinnnzzz
Implement a simple class called Zombie that represents a zombie character. The class should have the following features:
- A private attribute name of type std::string to store the name of the zombie.
- A constructor that takes a std::string parameter to initialize the name attribute.
- A public member function `announce()` that prints the zombie's name followed by " Braiiiiiiinnnzzz..." to the standard output.
- A destructor that prints a message indicating that the zombie with the given name is being destroyed.
- A function `randomChump` that creates a Zombie object on the stack, initializes it with a given name, and calls its `announce()` method.
- A function newZombie that creates a Zombie object on the heap, initializes it with a given name, and returns a pointer to it.
### Exercise 01: Moar Zombies
Create a class called ZombieHorde that represents a horde of zombies. The class should have the following features:
- A private attribute horde of type Zombie* to store an array of Zombie objects.
- A private attribute size of type int to store the number of zombies in the horde.
- A constructor that takes an int parameter to initialize the size attribute and dynamically allocates an array of Zombie objects.
- A public member function `announce()` that calls the `announce()` method for each zombie in the horde.
- A destructor that deallocates the memory used for the array of zombies.
- In the main function, create a ZombieHorde object with a specified number of zombies and call its `announce()` method to display the announcements of all zombies in the horde.
### Exercise 02: Hi This is Brainz
- A stringPTR variable that points to a string containing the name.
- A stringREF variable that is a reference to the same string.
- Print the memory addresses of the string, stringPTR, and stringREF variables.
- Print the values of the string using the string variable, the stringPTR pointer, and the stringREF reference.
### Exercise 03: Unnecessary Violence
Impement a Waepon class with the following features:
- A private attribute type of type std::string to store the type of the weapon.
- A constructor that takes a std::string parameter to initialize the type attribute.
- A public member function `getType()` that returns the type of the weapon.
- A public member function `setType()` that allows changing the type of the weapon.
- A HumanA class that represents a human character armed with a weapon. The class should have the following features:
- A private attribute name of type std::string to store the name of the human.
- A private attribute weapon of type Weapon& to store a reference to the weapon.
- A constructor that takes a std::string parameter for the name and a Weapon& parameter for the weapon.
- A public member function `attack()` that prints a message indicating that the human is attacking with their weapon.
- A HumanB class that represents a human character who can choose to arm themselves with a weapon later. The class should have the following features:
- A private attribute name of type std::string to store the name of the human.
- A private attribute weapon of type Weapon* to store a pointer to the weapon.
- A constructor that takes a std::string parameter for the name and initializes the weapon pointer to nullptr.
- A public member function `setWeapon()` that takes a Weapon& parameter and assigns it to the weapon pointer.
- A public member function `attack()` that prints a message indicating that the human is attacking with their weapon if it is set, or a message indicating that they are unarmed if the weapon pointer is nullptr.
### Exercise 04: Sed is for losers
- Create a program that takes three parameters in the following order: a filename and two strings, s1 and s2.
- It must open the file <filename> and copy its content into a new file <filename>.replace, replacing every occurrence of s1 with s2.
- Using C file manipulation functions is forbidden and will be considered cheating. All the member functions of the class std::string are allowed, except replace. Use them wisely!
### Exercise 05: Harl 2.0
Implement a class called Harl that represents a character who can complain at different levels. The class should have the following features:
- A public member function `complain()` that takes a std::string parameter level. The function should print a specific message based on the value of level. The possible levels are "DEBUG", "INFO", "WARNING", and "ERROR".
- If the level is "DEBUG", the function should print a message indicating that Harl is complaining at the DEBUG level.
- If the level is "INFO", the function should print a message indicating that Harl is complaining at the INFO level.
- If the level is "WARNING", the function should print a message indicating that Harl is complaining at the WARNING level.
- If the level is "ERROR", the function should print a message indicating that Harl is complaining at the ERROR level.
- If the level does not match any of the specified levels, the function should print a message indicating that Harl has nothing to complain about.
### Exercise 06: Harld Filter
Implement a system to filter what Harl says depending on the log levels I want to listen to.


## Module 02 - Ad-hoc polymorphism, operator overloading and the Orthodox Canonical class form -> [42-cpp-module02-en.subject.pdf](42-cpp-module02-en.subject.pdf)
Ad-hoc polymorphism, operator overloading and the Orthodox Canonical class form.
From now on, all the classes must be designed in the Orthodox Canonical Form, unless explicitly stated otherwise. They will then implement the four required member
functions below:
- Default constructor
- Copy constructor
- Copy assignment operator
- Destructor
Split the class code into two files. The header file (.hpp/.h) contains the class definition, whereas the source file (.cpp) contains the implementation.
### Exercise 00: My First Class in Orthodox Canonical Form9
Create a class called Fixed that represents a fixed-point number. The class should have the following features:
- A private attribute value of type int to store the fixed-point number.
- A private static constant attribute fractionalBits of type int to represent the number of fractional bits (set to 8).
- A default constructor that initializes the fixed-point number to 0.
- A copy constructor that creates a new Fixed object as a copy of an existing one.
- An assignment operator overload that allows assigning one Fixed object to another.
- A destructor that cleans up any resources used by the Fixed object.
- A public member function `getRawBits()` that returns the raw fixed-point value.
- A public member function `setRawBits()` that takes an int parameter and sets the raw fixed-point value.

### Exercise 01: Towards a more useful fixed-point number class
Enhance the Fixed class from Exercise 00 to include additional functionality for fixed-point arithmetic and conversions. The class should have the following features:
- A constructor that takes an int parameter to initialize the fixed-point number from an integer value.
- A constructor that takes a float parameter to initialize the fixed-point number from a floating-point value.
- A public member function `toFloat()` that converts the fixed-point number to a floating-point representation.
- A public member function `toInt()` that converts the fixed-point number to an integer representation.
- An overload of the insertion operator (<<) to allow easy output of the fixed-point number to an output stream.
- An overload of the extraction operator (>>) to allow easy input of the fixed-point number from an input stream.

### Exercise 02: Now we’re talking
Add polymorphic behavior to the Fixed class by implementing comparison operators and arithmetic operators. The class should have the following features:
- Overloads for the comparison operators (>, <, >=, <=, ==, !=) to compare two Fixed objects.
- Overloads for the arithmetic operators (+, -, *, /) to perform arithmetic operations between two Fixed objects.
- Overloads for the increment and decrement operators (prefix and postfix) to increase or decrease the fixed-point number by 1.
- Static member functions `min()` and `max()` that take two Fixed references and return the smaller or larger of the two, respectively.

### Exercise 03: BSP
Binary Space Partitioning (BSP) is a method for recursively subdividing a space into convex sets by hyperplanes. This subdivision gives rise to a representation of objects within the space that is useful for rendering, collision detection, and other spatial queries.
Now that I have a functional Fixed class, it would be nice to use it. Implement a function that indicates whether a point is inside a triangle or not. The function will take as parameters the three vertices of the triangle and the point to test. All these parameters will be Fixed instances.

## Module 03 - Inheritance -> [42-cpp-module03-en.subject.pdf](42-cpp-module03-en.subject.pdf)

### Exercise 00: Aaaaand... OPEN!
- implement CalpTrap class that represents a ClapTrap robot. The class should have the following features:
- A private attribute name of type std::string to store the name of the ClapTrap.
- Private attributes hitPoints, energyPoints, and attackDamage of type unsigned int to store the ClapTrap's hit points, energy points, and attack damage, respectively.
- A constructor that takes a std::string parameter to initialize the name attribute and sets default values for hitPoints, energyPoints, and attackDamage.
- A public member function `attack()` that takes a const std::string& parameter target. The function should print a message indicating that the ClapTrap is attacking the target, causing damage equal to attackDamage. The function should also decrease energyPoints by 1.
- A public member function `takeDamage()` that takes an unsigned int parameter amount. The function should decrease hitPoints by amount and print a message indicating the amount of damage taken.
- A public member function `beRepaired()` that takes an unsigned int parameter amount. The function should increase hitPoints by amount, decrease energyPoints by 1, and print a message indicating the amount of hit points repaired.
- A destructor that prints a message indicating that the ClapTrap is being destroyed.
### Exercise 01: Serena, my love!
- Implement a ScavTrap class that inherits from the ClapTrap class. The ScavTrap class should have the following features:
- A constructor that takes a std::string parameter to initialize the name attribute and sets default values for hitPoints, energyPoints, and attackDamage specific to ScavTrap.
- An overridden `attack()` function that takes a const std::string& parameter target. The function should print a message indicating that the ScavTrap is attacking the target, causing damage equal to attackDamage. The function should also decrease energyPoints by 1.
- A public member function `guardGate()` that prints a message indicating that the ScavTrap is now in Gate keeper mode.
- A destructor that prints a message indicating that the ScavTrap is being destroyed.
- ScavTrap will use the attributes of ClapTrap (update ClapTrap accordingly) and must initialize them to:
  - Name, which is passed as a parameter to the constructor
  - Hit points (100), representing the health of the ClapTrap
  - Energy points (50)
  - Attack damage (20)
- ScavTrap will also have its own special ability: `void guardGate();`
### Exercise 02: Repetitive work
- Implement a FragTrap class that inherits from the ClapTrap class. The FragTrap class should have the following features:
- A constructor that takes a std::string parameter to initialize the name attribute and sets default values for hitPoints, energyPoints, and attackDamage specific to FragTrap.
- An overridden `attack()` function that takes a const std::string& parameter target. The function should print a message indicating that the FragTrap is attacking the target, causing damage equal to attackDamage. The function should also decrease energyPoints by 1.
- A public member function `highFivesGuys()` that prints a positive high five message.
- A destructor that prints a message indicating that the FragTrap is being destroyed.
- Same goes for the attributes, but with different values this time:
  - Name, which is passed as a parameter to the constructor
  - Hit points (100), representing the health of the ClapTrap
  - Energy points (100)
  - Attack damage (30)
- FragTrap has a special ability too: `void highFivesGuys(void);`
### Exercise 03: Now it’s weird!
- Implement a DiamondTrap class that inherits from both ScavTrap and FragTrap classes. The DiamondTrap class should have the following features:
- A private attribute name of type std::string to store the name of the DiamondTrap.
- A constructor that takes a std::string parameter to initialize the name attribute. The constructor should also initialize the ClapTrap part of the DiamondTrap with the name appended by "_clap_name".
- A destructor that prints a message indicating that the DiamondTrap is being destroyed.
- Its attributes and member functions will be inherited from its parent classes:
  - Name, which is passed as a parameter to a constructor
  - ClapTrap::name (parameter of the constructor + "_clap_name" suffix)
  - Hit points (FragTrap)
  - Energy points (ScavTrap)
  - Attack damage (FragTrap)
  - `attack()` (ScavTrap)
- In addition to the special functions from both parent classes, DiamondTrap will have
- its own special ability: `void whoAmI();`

## Module 04 - Subtype Polymorphism, Abstract Classes, and Interfaces -> [42-cpp-module04-en.subject.pdf](42-cpp-module04-en.subject.pdf)

### Exercise 00: Polymorphism
- Implement a base class called Animal that represents a generic animal. The class should have the following features:
- A protected attribute type of type std::string to store the type of the animal.
- A default constructor that initializes the type attribute to "Animal".
- A virtual destructor.
- A public member function `getType()` that returns the type of the animal.
- A public virtual member function `makeSound()` that prints a generic animal sound.
- Implement derived classes Dog and Cat that inherit from the Animal class. Each derived class should have the following features:
- A default constructor that initializes the type attribute to "Dog" or "Cat", respectively.
- An overridden `makeSound()` function that prints a sound specific to the animal (e.g., "Woof!" for Dog and "Meow!" for Cat).
- In the main function, create an array of Animal pointers and populate it with Dog and Cat objects. Iterate through the array and call the `makeSound()` function for each animal to demonstrate polymorphism.
### Exercise 01: I don’t want to set the world on fire
Implement a Brain class. It contains an array of 100 std::string called ideas. This way, Dog and Cat will have a private Brain* attribute. Upon construction, Dog and Cat will create their Brain using new Brain(); Upon destruction, Dog and Cat will delete their Brain.
- Implement the copy constructor and the assignment operator for Dog and Cat to ensure a deep copy of the Brain attribute.
- In the main function, create instances of Dog and Cat, and demonstrate that copying one to another results in a deep copy of the Brain attribute. Modify the ideas in one instance and show that the other instance's ideas remain unchanged.

### Exercise 02: Abstract class
Creating Animal objects doesn’t make sense after all. It’s true, they make no sound!
To avoid any possible mistakes, the default Animal class should not be instantiable.
Fix the Animal class so that nobody can instantiate it. Everything should work as before.
If I want to, I can update the class name by adding an A prefix to Animal.

### Exercise 03: Interface & recap
Interfaces don’t exist in C++98 (not even in C++20). However, pure abstract classes are commonly called interfaces. Thus, in this last exercise, let’s try to implement interfaces in order to make sure I understand this module. Complete the definition of the following AMateria class and implement the necessary
member functions.
```
class AMateria
{
protected:
[...]
public:
AMateria(std::string const & type);
[...]
std::string const & getType() const; //Returns the materia type
virtual AMateria* clone() const = 0;
virtual void use(ICharacter& target);
};
```


## Module 05 - Repetition and Exceptions -> [42-cpp-module05-en.subject.pdf](42-cpp-module05-en.subject.pdf)

### Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!
Please note that exception classes do not have to be designed in Orthodox Canonical Form. However, every other class must follow it.
First, start with the smallest cog in this vast bureaucratic machine: the Bureaucrat Class.
- A private attribute name of type std::string to store the name of the bureaucrat.
- A private attribute grade of type int to store the bureaucrat's grade.
- A constructor that takes a std::string parameter for the name and an int parameter for the grade. The constructor should throw a GradeTooHighException if the grade is less than 1 and a GradeTooLowException if the grade is greater than 150.
- A public member function `getName()` that returns the name of the bureaucrat.
- A public member function `getGrade()` that returns the grade of the bureaucrat.
- A public member function `incrementGrade()` that decreases the grade by 1. If the resulting grade is less than 1, it should throw a GradeTooHighException.
- A public member function `decrementGrade()` that increases the grade by 1. If the resulting grade is greater than 150, it should throw a GradeTooLowException.
- Two exception classes GradeTooHighException and GradeTooLowException that inherit from std::exception. Each class should override the what() function to return an appropriate error message.
- An overload of the insertion operator (<<) to allow easy output of the bureaucrat's details to an output stream.
I will provide getters for both attributes: getName() and getGrade(). I must also implement two member functions to increment or decrement the bureaucrat’s grade. If the grade goes out of range, both functions must throw the same exceptions as the constructor.
### Exercise 01: Form up, maggots!
Now that I have bureaucrats, let’s give them something to do. What better activity could there be than filling out a stack of forms? Let’s create a Form class.
- A private attribute name of type std::string to store the name of the form.
- A private attribute gradeToSign of type int to store the grade required to sign the form.
- A private attribute gradeToExecute of type int to store the grade required to execute the form.
- A private attribute isSigned of type bool to store whether the form is signed or not.
- A constructor that takes a std::string parameter for the name, an int parameter for the gradeToSign, and an int parameter for the gradeToExecute. The constructor should throw a GradeTooHighException if either grade is less than 1 and a GradeTooLowException if either grade is greater than 150.

### Exercise 02: No, I need form 28B, not 28C...
Now that I have basic forms, it’s time to create a few more that actually do something. In all cases, the base class Form must be an abstract class and should therefore be renamed AForm. Keep in mind that the form’s attributes need to remain private and that they belong to the base class.
- Create three classes that inherit from AForm: ShrubberyCreationForm, RobotomyRequestForm, and PresidentialPardonForm.
- Each derived class should implement the `execute()` function to perform its specific action:
  - ShrubberyCreationForm: Creates a file named <target>_shrubbery and writes ASCII art of trees to it.
  - RobotomyRequestForm: Simulates a robotomy on the target. It should print drilling noises and inform that the target has been robotomized successfully 50% of the time. Otherwise, it should inform that the robotomy failed.
  - PresidentialPardonForm: Informs that the target has been pardoned by the president.
- Each derived class should have a constructor that takes a std::string parameter for the target and initializes the base class AForm with appropriate values for name, gradeToSign, and gradeToExecute.

### Exercise 03: At least this beats coffee-making
Since filling out forms all day would be too cruel for our bureaucrats, interns exist to take on this tedious task. In this exercise, I must implement the Intern class. The intern has no name, no grade, and no unique characteristics. The only thing bureaucrats care about is that they do their job.

However, the intern has one key ability: the `makeForm()` function. This function takes two strings as parameters: the first one represents the name of a form, and the second one represents the target of the form. It returns a pointer to a AForm object (corresponding to the form name passed as a parameter), with its target initialized to the second parameter.
- If the form name is unknown, the function should print an error message and return a null pointer.

## Module 06 - C++ casts -> [42-cpp-module06-en.subject.pdf](42-cpp-module06-en.subject.pdf)
For each exercise, type conversion must be handled using a specific type of casting.
The choice will be reviewed during the defense.
### Exercise 00: Conversion of scalar types
Write a class ScalarConverter that will contain only one static method "convert" that will take as a parameter a string representation of a C++ literal in its most common form and output its value in the following series of scalar types: char, int, float and double.
- The program must be able to convert the following types of literals:
  - char: a single displayable character surrounded by single quotes (e.g., 'a').
  - int: a whole number without any decimal point (e.g., 42).
  - float: a number with a decimal point followed by an 'f' (e.g., 42.0f).
  - double: a number with a decimal point (e.g., 42.0).
- The program must handle special floating-point values such as:
  - +inff, -inff, nanf for float
  - +inf, -inf, nan for double
- The program must handle edge cases and invalid inputs gracefully, providing appropriate error messages when conversion is not possible.
- The output format must be as follows:
```
char: 'c' or Non displayable or impossible
int: 42 or impossible
float: 42.0f or impossible
double: 42.0 or impossible
```

### Exercise 01: Serialization
Implement a class Serializer which will not be initializable by the user in any way,
with the following static methods:
- `uintptr_t serialize(Data* ptr);` It takes a pointer and converts it to the unsigned integer type uintptr_t.
- `Data* deserialize(uintptr_t raw);` It takes an unsigned integer parameter and converts it to a pointer to Data.
- A simple struct Data containing at least one member variable of the choice.
Use `serialize()` on the address of the Data object and pass its return value to `deserialize()`. Then, ensure the return value of `deserialize()` compares equal to the original pointer

### Exercise 02: Identify real type
Implement a Base class that has a public virtual destructor only. Create three empty classes A, B, and C, that publicly inherit from Base. These four classes don’t have to be designed in the Orthodox Canonical Form.
- Implement two functions to identify the real type of an object pointed to by a Base class pointer or reference:
- `void identify(Base* p);` This function takes a pointer to Base as a parameter and identifies the actual derived type of the object pointed to by p. It should print "A", "B", or "C" depending on the actual type.
- `void identify(Base& p);` This function takes a reference to Base as a parameter and identifies the actual derived type of the object pointed to by p. It should print "A", "B", or "C" depending on the actual type.
- Create instances of A, B, and C, and use both identify functions to demonstrate their functionality.
- Handle any exceptions that may arise during type identification.
- `typeinfo` from `<typeinfo>` header is not allowed.

## Module 07 - C++ templates -> [42-cpp-module07-en.subject.pdf](42-cpp-module07-en.subject.pdf)

### Exercise 00: Start with a few functions
- Implement a function template `swap` that takes two references of the same type and swaps their values.
- Implement a function template `min` that takes two references of the same type and returns the smaller of the two.
- Implement a function template `max` that takes two references of the same type and returns the larger of the two.
- Test the function templates with different data types (e.g., int, float, std::string) to ensure they work correctly.
- Templates must be defined in the header files.
```
int
main( void ) {
int a = 2;
int b = 3;
::swap( a, b );
std::cout << "a = " << a << ", b = " << b << std::endl;
std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
std::string c = "chaine1";
std::string d = "chaine2";
::swap(c, d);
std::cout << "c = " << c << ", d = " << d << std::endl;
std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
return 0;
}
```
Here is the expected output:
```
a = 3, b = 2
min(a, b) = 2
max(a, b) = 3
c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2
```
### Exercise 01: Iter
Implement a function template iter that takes 3 parameters and returns nothing.
- The first parameter is the address of an array.
- The second one is the length of the array, passed as a const value.
- The third one is a function that will be called on every element of the array.
- Test the iter function with different data types (e.g., int, char, std::string) and different functions to ensure it works correctly.
```
int
main( void ) {
int a[] = { 0, 1, 2, 3, 4 };
::iter( a, 5, print<int> );
char b[] = { 'a', 'b', 'c', 'd', 'e' };
::iter( b, 5, print<char> );
std::string c[] = { "chaine1", "chaine2", "chaine3", "chaine4", "chaine5" };
::iter( c, 5, print<std::string> );
return 0;
}
```
Here is the expected output:
```
0
1
2
3
4
a
b
c
d
e
chaine1
chaine2
chaine3
chaine4
chaine5
```

### Exercise 02: Array
Develop a class template Array that contains elements of type T and that implements
the following behavior and functions:
- Construction with no parameter: Creates an empty array.
- Construction with an unsigned int n as a parameter: Creates an array of n elements initialized by default. Tip: Try to compile `int * a = new int()`; then display `*a`.
- Construction by copy and assignment operator. In both cases, modifying either the original array or its copy after copying musn’t affect the other array.
- I MUST use the operator new[] to allocate memory. Preventive allocation (allocating memory in advance) is forbidden. The program must never access non-allocated memory.
- Elements can be accessed through the subscript operator: [ ].
- When accessing an element with the [ ] operator, if its index is out of bounds, an std::exception is thrown.
- A member function size() that returns the number of elements in the array. This member function takes no parameters and must not modify the current instance.

## Module 08 - Templated containers, iterators, algorithms -> [42-cpp-module08-en.subject.pdf](42-cpp-module08-en.subject.pdf)
I will notice that, in this module, the exercises can be solved WITHOUT the standard Containers and WITHOUT the standard Algorithms.

However, using them is precisely the goal of this Module.
Thus, do the best to apply them wherever it’s appropriate.

I will get a very bad grade if I don’t, even if the code works as expected. Please don’t be lazy.
I can define the templates in the header files as usual. Or, if I want to, I can write the template declarations in the header files and write their implementations in .tpp files. In any case, the header files are mandatory while the .tpp files are optional.
### Exercise 00: Easy find
Write a function template easyfind that accepts a type T. It takes two parameters: the first one is of type T, and the second one is an integer.
Assuming T is a container of integers, this function has to find the first occurrence of the second parameter in the first parameter.
If no occurrence is found, I can either throw an exception or return an error value of the choice. If I need some inspiration, analyze how standard containers behave.
I don’t have to handle associative containers.

### Exercise 01: Span
Develop a Span class that can store a maximum of N integers. N is an unsigned int variable and will be the only parameter passed to the constructor.
This class will have a member function called `addNumber()` to add a single number to the Span. It will be used in order to fill it. Any attempt to add a new element if there are already N elements stored should throw an exception.
Next, implement two member functions: `shortestSpan()` and `longestSpan()`
They will respectively find out the shortest span or the longest span (or distance, if I prefer) between all the numbers stored, and return it. If there are no numbers stored, or only one, no span can be found. Thus, throw an exception.
Of course, I will write the own tests, and they will be far more thorough than the ones below. Test the Span with at least 10,000 numbers. More would be even better.
```
int main()
{
Span sp = Span(5);
sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);
std::cout << sp.shortestSpan() << std::endl;
std::cout << sp.longestSpan() << std::endl;
return 0;
}
```
Should output:
```
$> ./ex01
2
14
$>
```
Last but not least, it would be wonderful to fill the Span using a range of iterators.
Making thousands of calls to `addNumber()` is so annoying. Implement a member function to add multiple numbers to the Span in a single call.
### Exercise 02: Mutated abomination
Now, it’s time to move on to more serious things. Let’s develop something weird.
The std::stack container is very nice. Unfortunately, it is one of the only STL Containers that is NOT iterable. That’s too bad.
But why would we accept this? Especially if we can take the liberty of butchering the original stack to create missing features.
To repair this injustice, I have to make the std::stack container iterable.
Write a MutantStack class. It will be implemented in terms of a std::stack.
It will offer all its member functions, plus an additional feature: iterators.
```
int main()
{
MutantStack<int>
mstack;
mstack.push(5);
mstack.push(17);
std::cout << mstack.top() << std::endl;
mstack.pop();
std::cout << mstack.size() << std::endl;
mstack.push(3);
mstack.push(5);
mstack.push(737);
//[...]
mstack.push(0);
MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
++it;
--it;
while (it != ite)
{
std::cout << *it << std::endl;
++it;
}
std::stack<int> s(mstack);
return 0;
}
```
Should output:
```
$> ./ex02
17
5
3
5
737
0
$>
```
If I run it a first time with the MutantStack, and a second time replacing the
MutantStack with, for example, a std::list, the two outputs should be the same. Of
course, when testing another container, update the code below with the corresponding
member functions (`push()` can become `push_back()`)
## Module 09 - STL (Standard Template Library)-> [42-cpp-module09-en.subject.pdf](42-cpp-module09-en.subject.pdf)
It is mandatory to use the standard containers to perform each exercise in this module.
Once a container is used I cannot use it for the rest of the module.
It is advisable to read the subject in its entirety before doing the exercises.
I must use at least one container for each exercise with the exception of exercise 02 which requires the use of two containers.
I must submit a Makefile for each program which will compile the source files to the required output with the flags -Wall, -Wextra and -Werror.
I must use c++, and the Makefile must not relink.
The Makefile must at least contain the rules $(NAME), all, clean, fclean and re.

### Exercise 00: Bitcoin Exchange
I have to create a program which outputs the value of a certain amount of bitcoin on a certain date.
This program must use a database in csv format which will represent bitcoin price over time. This database is provided with this subject.
The program will take as input a second database, storing the different prices/dates to evaluate.
The program must respect these rules:
- The program name is btc.
- the program must take a file as an argument.
- Each line in this file must use the following format: "date | value".
- A valid date will always be in the following format: Year-Month-Day.
- A valid value must be either a float or a positive integer, between 0 and 1000.
- For each line in the input file, the program must output the result of the multiplication between the value and the bitcoin price on that date.
Here is an example of an input.txt file:
```
$> head input.txt
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648
$>
```
The program will use the value in the input file.
The program should display on the standard output the result of the value multiplied by the exchange rate according to the date indicated in the database.
If the date used in the input does not exist in the DB then I must use the closest date contained in the DB. Be careful to use the lower date and not the upper one. The following is an example of the program’s use.
```
$> ./btc
Error: could not open file.
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
$>
```
I must use at least one container in the code to validate this exercise.
### Exercise 01: Reverse Polish Notation
The program name is RPN.
- The program must take an inverted Polish mathematical expression as an argument.
- The numbers used in this operation and passed as arguments will always be less than 10. The calculation itself but also the result do not take into account this rule.
- The program must process this expression and output the correct result on the standard output.
- If an error occurs during the execution of the program an error message should be displayed on the standard error.
- The program must be able to handle operations with these tokens: "+ - / *".
I must use at least one container in the code to validate this exercise.
I don’t need to handle brackets or decimal numbers.
Here is an example of standard usage:
```
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
$>
```
Warning: The container(s) I used in the previous exercise are forbidden here. The container(s) I used to validate this exercise will not be usable for the rest of this module.
### Exercise 02: PmergeMe
I must create a program with these constraints:
- The name of the program is PmergeMe.
- The program must be able to use a positive integer sequence as an argument.
- The program must use the merge-insert sort algorithm to sort the positive integer sequence.

To clarify, yes, I need to use the Ford-Johnson algorithm. (source: Art Of Computer Programming, Vol.3. Merge Insertion, Page 184.)
- If an error occurs during program execution, an error message should be displayed on the standard error.
I must use at least two different containers in The code to validate this exercise. The program must be able to handle at least 3000 different integers.

It is strongly advised to implement the algorithm for each container and thus to avoid using a generic function.
Here are some additional guidelines on the information I should display line by line on the standard output:
- On the first line I must display an explicit text followed by the unsorted positive integer sequence.
- On the second line I must display an explicit text followed by the sorted positive integer sequence.
- On the third line, I must display an explicit message indicating the time taken by the algorithm, specifying the first container used to sort the positive integer sequence.
- On the last line I must display an explicit text indicating the time used by the algorithm by specifying the second container used to sort the positive integer sequence.
The format for the display of the time used to carry out the sorting is free but the precision chosen must allow to clearly see the difference between the two containers used. Here is an example of standard use:
```
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After:
3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
$> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
Before: 141 79 526 321 [...]
After:
79 141 321 526 [...]
Time to process a range of 3000 elements with std::[..] : 62.14389 us
Time to process a range of 3000 elements with std::[..] : 69.27212 us
$> ./PmergeMe "-1" "2"
Error
$> # For OSX USER:
$> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
[...]
$>
```
The indication of the time is deliberately strange in this example.
Of course I have to indicate the time used to perform all the operations, both the sorting part and the data management part.
Warning: The container(s) I used in the previous exercises are forbidden here.
The management of errors related to duplicates is left to the discretion.