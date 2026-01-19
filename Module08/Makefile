NAME = Module08Tests

GREEN  = \e[0;32m
YELLOW = \e[0;33m
CYAN   = \e[0;36m
RESET  = \e[0m

BUILD_DIR   := build
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Debug
EXERCISES   := 00 01 02
EXERCISE_DIRS := $(addprefix ex, $(EXERCISES))

.PHONY: all
all: build_all test

.PHONY: configure
configure:
	@$(shell export GTEST_COLOR=yes)
	@printf "$(CYAN)Configuring CMake...$(RESET)\n"
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake $(CMAKE_FLAGS) ..

.PHONY: build_cmake
build_cmake: configure
	@printf "$(CYAN)Building...$(RESET)\n"
	@cd $(BUILD_DIR) && make

.PHONY: test
test: build_cmake
	@printf "$(CYAN)Running tests...$(RESET)\n"
	@cd $(BUILD_DIR) && ctest --output-on-failure

.PHONY: build_exercises
build_exercises:
	@for dir in $(EXERCISE_DIRS); do [ -d $$dir ] && $(MAKE) -C $$dir; done

.PHONY: build_all
build_all: build_cmake build_exercises

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@for dir in $(EXERCISE_DIRS); do [ -d $$dir ] && $(MAKE) -C $$dir clean; done 2>/dev/null || true

.PHONY: fclean
fclean: clean
	@for dir in $(EXERCISE_DIRS); do [ -d $$dir ] && $(MAKE) -C $$dir fclean; done 2>/dev/null || true

.PHONY: re
re: fclean all
