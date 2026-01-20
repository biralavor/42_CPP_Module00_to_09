find_package(GTest REQUIRED)

# Create test executable for ex00
add_executable(Module00Ex00Tests
    TestModule00Ex00.cpp
)

# Configure test executable for ex00
target_link_libraries(Module00Ex00Tests PRIVATE
    GTest::GTest 
    GTest::Main
    megaphone_lib
)

# Create test executable for ex01
add_executable(Module00Ex01Tests
    TestModule00Ex01.cpp
)

target_link_libraries(Module00Ex01Tests PRIVATE
    GTest::GTest 
    GTest::Main
    phonebook_lib
)

# Create test executable for ex02
add_executable(Module00Ex02Tests
    TestModule00Ex02.cpp
)

target_link_libraries(Module00Ex02Tests PRIVATE
    GTest::GTest 
    GTest::Main
    account_lib
)

# Register individual GoogeTest cases
include (GoogleTest)
gtest_discover_tests(Module00Ex00Tests)
gtest_discover_tests(Module00Ex01Tests)
gtest_discover_tests(Module00Ex02Tests)

# Register tests
add_test(
    NAME Module00_Ex00_Test
    COMMAND Module00Ex00Tests
)

add_test(
    NAME Module00_Ex01_Test
    COMMAND Module00Ex01Tests
)

add_test(
    NAME Module00_Ex02_Test
    COMMAND Module00Ex02Tests
)