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
EXERCISE_DIRS := $(wildcard ex*)

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
	@cd $(BUILD_DIR) && make
	@printf "$(GREEN)CMake build complete$(RESET)\n"

.PHONY: test
test: build_cmake
	@printf "$(CYAN)Running tests...$(RESET)\n"
	@cd $(BUILD_DIR) && ctest --output-on-failure
	@printf "$(GREEN)Tests completed$(RESET)\n"

.PHONY: clean_cmake
clean_cmake:
	@rm -rf $(BUILD_DIR)
	@printf "$(GREEN)Build directory cleaned$(RESET)\n"

.PHONY: re
re: clean all

# ********************************************* #
#   INDIVIDUAL EXCERCISE BUILD SYSTEM TARGETS   #
# ********************************************* #

.PHONY: build_exercises
build_exercises:
	@printf "$(CYAN)Building individual exercises...$(RESET)\n"
	@for dir in $(EXERCISE_DIRS); do \
		if [ -d $$dir ]; then \
			$(MAKE) -C $$dir; \
		fi; \
	done
	@printf "$(GREEN)All exercises built successfully!$(RESET)\n"

.PHONY: clean_exercises
clean_exercises:
	@printf "$(YELLOW)Cleaning individual exercises...$(RESET)\n"
	@for dir in $(EXERCISE_DIRS); do \
		if [ -d $$dir ]; then \
			$(MAKE) -C $$dir clean; \
		fi; \
	done
	@printf "$(GREEN)Individual exercise cleaned$(RESET)\n"

.PHONY: fclean_exercises
fclean_exercises:
	@printf "$(CYAN)Forcing clean of individual exercise program files...$(RESET)\n"
	@for dir in $(EXERCISE_DIRS); do \
		if [ -d $$dir ]; then \
			$(MAKE) -C $$dir fclean; \
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
	@printf "  $(GREEN)build_cmake$(RESET)       - Build with CMake system\n"
	@printf "  $(GREEN)build_exercises$(RESET)   - Build individual exercises\n"
	@printf "  $(GREEN)build_all$(RESET)         - Build with both systems\n"
	@printf "  $(GREEN)clean$(RESET)             - Clean both systems\n"
	@printf "  $(GREEN)fclean$(RESET)            - Deep clean both systems\n"
	@printf "  $(GREEN)help$(RESET)              - Show this help\n"
