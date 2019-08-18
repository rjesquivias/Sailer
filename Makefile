CXX = g++
CXX_FLAGS = -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow

# Final binary
BIN = mybin
TEST_BIN = testbin
# Put all auto generated stuff to this build dir.
BUILD_DIR = build
TEST_BUILD_DIR = test/build

# List of all .cpp source files.
CPP = $(wildcard src/*.cpp)
TEST_CPP = $(wildcard test/*.cpp)

# All .o files go to build dir.
OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJ = $(TEST_CPP:%.cpp=$(TEST_BUILD_DIR)/%.o)

# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)
TEST_DEP = $(TEST_OBJ:%.o=%.d)

# Default target named after the binary.
$(BIN) : $(BUILD_DIR)/$(BIN)

# Actual target of the binary - depends on all .o files.
$(BUILD_DIR)/$(BIN) : $(OBJ)
    # Create build directories - same structure as sources.
	mkdir -p $(@D)
    # Just link all the object files.
	$(CXX) $(CXX_FLAGS) $^ -o $@

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
    # The -MMD flags additionaly creates a .d file with
    # the same name as the .o file.
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

.PHONY : clean test

clean :
    # This should remove all generated files.
	-rm $(BUILD_DIR)/$(BIN) $(OBJ) $(DEP)
	-rm $(TEST_BUILD_DIR)/$(TEST_BIN) $(TEST_OBJ) $(TEST_DEP)

test: $(TEST_BIN)

$(TEST_BIN) : $(TEST_BUILD_DIR)/$(TEST_BIN)

$(TEST_BUILD_DIR)/$(TEST_BIN) : $(TEST_OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $^ -o $@

-include $(TEST_DEP)

$(TEST_BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

