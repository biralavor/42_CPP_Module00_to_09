NAME = Module05Tests

# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #
GREEN  = \e[0;32m
YELLOW = \e[0;33m
CYAN   = \e[0;36m
RESET  = \e[0m

# **************************************************************************** #
#                                VARIABLES                                     #
# **************************************************************************** #
BUILD_DIR   := build
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Debug

EXERCISES     := 00 01 02 03
EXERCISE_DIRS := $(addprefix ex, $(EXERCISES))

# **************************************************************************** #
#                                 TARGETS                                      #
# **************************************************************************** #

.PHONY: all
all: build_all test

# ********************************************* #
#              GOOGLE TESTS TARGETS             #
# ********************************************* #

.PHONY: configure
configure:
	@$(shell export GTEST_COLOR=yes)
	@printf "$(CYAN)Configuring CMake build system...$(RESET)\n"
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake $(CMAKE_FLAGS) ..
	@printf "$(GREEN)CMake files generated in $(YELLOW)$(BUILD_DIR)$(RESET)\n"

.PHONY: build_cmake
build_cmake: configure
	@printf "$(CYAN)Building with CMake...$(RESET)\n"
	@cd $(BUILD_DIR) && make --no-print-directory
	@printf "$(GREEN)CMake build complete$(RESET)\n"

.PHONY: test
test: build_cmake
	@printf "$(CYAN)Running tests...$(RESET)\n"
	@cd $(BUILD_DIR) && ctest --output-on-failure
	@printf "$(GREEN)Tests completed$(RESET)\n"

.PHONY: test-ex00
test-ex00: build_cmake
	@printf "$(CYAN)Running ex00 tests...$(RESET)\n"
	@cd $(BUILD_DIR) && ./tests/TestModule05Ex00
	@printf "$(GREEN)ex00 tests completed$(RESET)\n"

.PHONY: test-ex01
test-ex01: build_cmake
	@printf "$(CYAN)Running ex01 tests...$(RESET)\n"
	@cd $(BUILD_DIR) && ./tests/TestModule05Ex01
	@printf "$(GREEN)ex01 tests completed$(RESET)\n"

.PHONY: test-ex02
test-ex02: build_cmake
	@printf "$(CYAN)Running ex02 tests...$(RESET)\n"
	@cd $(BUILD_DIR) && ./tests/TestModule05Ex02
	@printf "$(GREEN)ex02 tests completed$(RESET)\n"

.PHONY: test-ex03
test-ex03: build_cmake
	@printf "$(CYAN)Running ex03 tests...$(RESET)\n"
	@cd $(BUILD_DIR) && ./tests/TestModule05Ex03
	@printf "$(GREEN)ex03 tests completed$(RESET)\n"

.PHONY: clean_cmake
clean_cmake:
	@rm -rf $(BUILD_DIR)
	@printf "$(GREEN)Build directory cleaned$(RESET)\n"

.PHONY: re
re: clean_cmake all

# ********************************************* #
#   INDIVIDUAL EXCERCISE BUILD SYSTEM TARGETS   #
# ********************************************* #

.PHONY: build_exercises
build_exercises:
	@printf "$(CYAN)Building individual exercises...$(RESET)\n"
	@for dir in $(EXERCISE_DIRS); do \
		if [ -d $$dir ]; then \
			$(MAKE) -C $$dir --no-print-directory; \
		fi; \
	done
	@printf "$(GREEN)All exercises built successfully!$(RESET)\n"

.PHONY: clean_exercises
clean_exercises:
	@printf "$(YELLOW)Cleaning individual exercises...$(RESET)\n"
	@for dir in $(EXERCISE_DIRS); do \
		if [ -d $$dir ]; then \
			$(MAKE) -C $$dir clean --no-print-directory;  \
		fi; \
	done
	@printf "$(GREEN)Individual exercise cleaned$(RESET)\n"

.PHONY: fclean_exercises
fclean_exercises:
	@printf "$(CYAN)Forcing clean of individual exercise program files...$(RESET)\n"
	@for dir in $(EXERCISE_DIRS); do \
		if [ -d $$dir ]; then \
			$(MAKE) -C $$dir fclean --no-print-directory; \
		fi; \
	done

.PHONY: build_all
build_all: build_cmake build_exercises
	@printf "$(GREEN)All builds completed$(RESET)\n"

.PHONY: clean_cmake clean_exercises
clean: clean_cmake clean_exercises
	@printf "$(CYAN)Cleaning all build directories...$(RESET)\n"

.PHONY: fclean
fclean: clean_cmake fclean_exercises
	@printf "$(CYAN)Forcing clean of all build directories...$(RESET)\n"

# ********************************************* #
#                  HELP TARGETS                 #
# ********************************************* #
help:
	@printf "$(CYAN)// Available targets: //$(RESET)\n"
	@printf "  $(GREEN)test$(RESET)              - Run all tests (CMake system)\n"
	@printf "  $(GREEN)test-ex00$(RESET)         - Run ex00 tests only\n"
	@printf "  $(GREEN)test-ex01$(RESET)         - Run ex01 tests only\n"
	@printf "  $(GREEN)test-ex02$(RESET)         - Run ex02 tests only\n"
	@printf "  $(GREEN)test-ex03$(RESET)         - Run ex03 tests only\n"
	@printf "  $(GREEN)build_cmake$(RESET)       - Build with CMake system\n"
	@printf "  $(GREEN)build_exercises$(RESET)   - Build individual exercises\n"
	@printf "  $(GREEN)build_all$(RESET)         - Build with both systems\n"
	@printf "  $(GREEN)clean$(RESET)             - Clean both systems\n"
	@printf "  $(GREEN)fclean$(RESET)            - Deep clean both systems\n"
	@printf "  $(GREEN)help$(RESET)              - Show this help\n"
