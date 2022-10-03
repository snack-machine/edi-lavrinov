# Recipe for building a Binary Search Tree
BUILD_TARGET = binary_tree_build
SOURCE_CODE_FOLDER = source_code/
BUILD_FOLDER = build/
OBJ_FOLDER = $(BUILD_FOLDER)obj/


SOURCE_CODE = $(wildcard $(SOURCE_CODE_FOLDER)*.c)
OBJ = $(patsubst $(SOURCE_CODE_FOLDER)%.c, $(OBJ_FOLDER)%.o, $(SOURCE_CODE))


build: $(OBJ)
	gcc $(OBJ) -o $(BUILD_FOLDER)$(BUILD_TARGET)

$(OBJ_FOLDER)%.o: $(SOURCE_CODE_FOLDER)%.c
	bash -c "if [ ! -d "$(OBJ_FOLDER)" ]; then mkdir -p $(OBJ_FOLDER); fi" 
	gcc -c $< -o $@

clean: 
	rm -r build



# # Recipe for building Unit Tests

# UT_TARGET = unit_tests_build
# UT_FOLDER = unit_tests/
# UT_BUILD_FOLDER = build/
# UT_OBJ_FOLDER = $(UT_BUILD_FOLDER)obj2/
# LIBS = -lcunit

# UT_SOURCE_CODE = $($(UT_FOLDER)unit_tests.c $(SOURCE_CODE_FOLDER)binary_tree.c)
# UT_OBJ = $($(UT_FOLDER)unit_tests.o $(SOURCE_CODE_FOLDER)binary_tree.o)

# $(UT_TARGET: $(UT_SOURCE_CODE)
# 	gcc $(UT_OBJ) -o $(UT_BUILD_FOLDER)$(UT_TARGET)

# $(UT_OBJ_FOLDER)%.o: $(UT_SOURCE_CODE)%.c
# 	bash -c "if [ ! -d "$(UT_OBJ_FOLDER)" ]; then mkdir -p $(UT_OBJ_FOLDER); fi" 
# 	gcc -c $< -o $@

