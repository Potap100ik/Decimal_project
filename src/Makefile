# ==============================================================================
# VARIABLES
# ==============================================================================

# --- Tools ---
CC := gcc
AR := ar
GCOV_TOOL := gcov
LCOV := lcov
GENHTML := genhtml
CLANG_FORMAT := clang-format
CPPCHECK := cppcheck
LEAKS := leaks
VALGRIND := valgrind

# --- Project Files ---
LIB_NAME := h_decimal.a
HEADERS := $(wildcard *.h)
### === исключение функции decimal_print из lib
SANDBOX_SRC := h_decimal_print.c
# SANDBOX_SRC := 
LIB_SOURCES := $(filter-out $(SANDBOX_SRC), $(wildcard *.c))
### === работа в main() внутри sandbox/main_check.c через "make test" 
# TEST_DIR := sandbox
TEST_DIR := test
### ===
TEST_MAIN_SRC := $(TEST_DIR)/main_check.c
TEST_CASE_SOURCES := $(wildcard $(TEST_DIR)/test_h_*.c)
TEST_CASE_HEADERS := $(wildcard $(TEST_DIR)/test_h_*.h)
ALL_SOURCES := $(LIB_SOURCES) $(TEST_MAIN_SRC) $(TEST_CASE_SOURCES)
ALL_HEADERS := $(HEADERS) $(TEST_CASE_HEADERS)
CLANG_FORMAT_SOURCE := ../format/.clang-format
CLANG_FORMAT_FILE := .clang-format

# --- Build Directories ---
BUILD_DIR := bin
COV_BUILD_DIR := bin_cov
COV_DIR := coverage_report
COV_INFO := $(COV_DIR)/coverage.info

# --- Build Flags ---
CFLAGS := -std=c11 -Wall -Wextra -Werror -D_POSIX_C_SOURCE=200809L
# CFLAGS += -g -O0
LDFLAGS :=
COV_FLAGS := --coverage

# --- OS-specific libraries ---
ifeq ($(shell uname -s), Darwin)
    LDFLAGS += -lcheck -lm
else
    LDFLAGS += -lcheck -lm -lsubunit -pthread -lrt
endif

# --- Object Files (Normal Build) ---
LIB_OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(LIB_SOURCES:.c=.o)))
TEST_OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_CASE_SOURCES:.c=.o)))
TEST_MAIN_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_MAIN_SRC:.c=.o)))
TEST_ALL_OBJECTS := $(TEST_OBJECTS) $(TEST_MAIN_OBJ)

# --- Object Files (Coverage Build) ---
COV_LIB_OBJECTS := $(addprefix $(COV_BUILD_DIR)/, $(notdir $(LIB_SOURCES:.c=.o)))
COV_TEST_OBJECTS := $(addprefix $(COV_BUILD_DIR)/, $(notdir $(TEST_CASE_SOURCES:.c=.o)))
COV_TEST_MAIN_OBJ := $(addprefix $(COV_BUILD_DIR)/, $(notdir $(TEST_MAIN_SRC:.c=.o)))
COV_ALL_OBJECTS := $(COV_LIB_OBJECTS) $(COV_TEST_OBJECTS) $(COV_TEST_MAIN_OBJ)

# --- Executables ---
TEST_RUNNER := $(BUILD_DIR)/test_runner
COV_RUNNER := $(COV_BUILD_DIR)/cov_runner

# ==============================================================================
# PHONY & MAIN TARGETS
# ==============================================================================

.PHONY: all clean rebuild test gcov_report review copy-format check-format cppcheck leaks valgrind help build docker format sandbox

all: build $(TEST_RUNNER)

build: $(LIB_NAME) $(TEST_RUNNER)

rebuild: clean all

# Create build directories
$(BUILD_DIR):
	@mkdir -p $@
$(COV_BUILD_DIR):
	@mkdir -p $@

# ==============================================================================
# LIBRARY BUILD RULES
# ==============================================================================

$(LIB_NAME): $(LIB_OBJECTS)
	$(AR) rcs $@ $^
	ranlib $@

$(BUILD_DIR)/%.o: %.c $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ==============================================================================
# TEST BUILD & RUN RULES
# ==============================================================================


sandbox:
	$(MAKE) test TEST_DIR=sandbox SANDBOX_SRC=


test: clean $(TEST_RUNNER)
	./$(TEST_RUNNER)

$(TEST_RUNNER): $(TEST_ALL_OBJECTS) $(LIB_NAME)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ 

# Rule for compiling test sources into bin/
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ==============================================================================
# COVERAGE REPORT RULES
# ==============================================================================

gcov_report: $(COV_RUNNER)
	@echo "--- Running coverage-enabled tests ---"
	./$(COV_RUNNER)
	@echo "--- Generating GCOV report ---"
	@mkdir -p $(COV_DIR)
	$(LCOV) --capture --directory . --output-file $(COV_INFO)
	$(LCOV) --remove $(COV_INFO) '/usr/*' --ignore-errors unused --output-file $(COV_INFO) 
	$(GENHTML) $(COV_INFO) --output-directory $(COV_DIR)
	@echo "Coverage report generated in $(COV_DIR)/index.html"
ifeq ($(shell uname -s), Darwin)
	open $(COV_DIR)/index.html
endif

# Rule to build the coverage runner
$(COV_RUNNER): $(COV_ALL_OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(COV_FLAGS) -o $@

# Rule to compile library sources with coverage flags into bin_cov/
$(COV_BUILD_DIR)/%.o: %.c $(HEADERS) | $(COV_BUILD_DIR)
	$(CC) $(CFLAGS) $(COV_FLAGS) -c $< -o $@

# Rule to compile test sources without coverage flags into bin_cov/
$(COV_BUILD_DIR)/%.o: $(TEST_DIR)/%.c $(HEADERS) | $(COV_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ==============================================================================
# CLEANING RULES
# ==============================================================================

clean:
	@echo "--- Cleaning build artifacts ---"
	rm -rf $(BUILD_DIR) $(COV_BUILD_DIR) $(COV_DIR) $(LIB_NAME) *.gcda *.gcno *.gcov *.info $(TEST_DIR)/$(CLANG_FORMAT_FILE) $(CLANG_FORMAT_FILE)

# ==============================================================================
# REVIEW TARGETS
# ==============================================================================

ifeq ($(shell uname -s), Darwin)
MEM_CHECK_TARGET := leaks
else
MEM_CHECK_TARGET := valgrind
endif

copy-format:
	cp $(CLANG_FORMAT_SOURCE) $(CLANG_FORMAT_FILE)

check-format: copy-format
	$(CLANG_FORMAT) -n $(ALL_SOURCES) $(HEADERS)

cppcheck:
	$(CPPCHECK) --enable=all \
	--suppress=staticFunction \
	--suppress=missingIncludeSystem \
	--check-level=exhaustive \
	$(ALL_SOURCES)

leaks: $(TEST_RUNNER)
ifeq ($(shell uname -s), Darwin)
	CK_FORK=no $(LEAKS) --atExit -- ./$(TEST_RUNNER)
else
	@echo "Leaks target is only available on macOS."
endif

valgrind: $(TEST_RUNNER)
ifeq ($(shell uname -s), Linux)
	CK_FORK=no $(VALGRIND) ./$(TEST_RUNNER)
else
	@echo "Valgrind target is only available on linux."
endif


# ==============================================================================
# HELP TARGET
# ==============================================================================
format: copy-format
	$(CLANG_FORMAT) -i $(ALL_SOURCES) $(ALL_HEADERS)
open_report: gcov_report
	open coverage_report/index.html &
help:
	@echo "Available targets:"
	@echo "  all           - Build the static library ($(LIB_NAME)) in the root and the test runner in $(BUILD_DIR)"
	@echo "  build         - Alias for 'all'"
	@echo "  test          - Build and run tests from $(BUILD_DIR)"
	@echo "  gcov_report   - Generate and open a test coverage report from $(COV_BUILD_DIR)"
	@echo "  leaks         - Run tests with memory leak checking using Leaks (macOS only)"
	@echo "  valgrind      - Run tests with memory leak checking using Valgrind (Linux only)"
	@echo "  cppcheck      - Run static analysis with cppcheck"
	@echo "  check-format  - Check the formatting of all source code using clang-format"
	@echo "  clean         - Remove all build artifacts and reports"
	@echo "  rebuild       - Force a clean and full rebuild"
