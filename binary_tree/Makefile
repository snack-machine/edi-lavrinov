# Recipe for building a Binary Search Tree and unit tests fot it

BUILD_TARGET = binary_tree_build
SOURCE_CODE_FOLDER = source_code/
BUILD_FOLDER = build/
OBJ_FOLDER = $(BUILD_FOLDER)obj/

SOURCE_CODE = $(wildcard $(SOURCE_CODE_FOLDER)*.c)
OBJ = $(patsubst $(SOURCE_CODE_FOLDER)%.c, $(OBJ_FOLDER)%.o, $(SOURCE_CODE))

UT_TARGET = unit_tests_build
UT_FOLDER = unit_tests/
UT_BUILD_FOLDER = build/
UT_OBJ_FOLDER = $(UT_BUILD_FOLDER)obj2/
LIBS = -lcunit


build: $(OBJ)
	gcc $(OBJ) -o $(BUILD_FOLDER)$(BUILD_TARGET)

$(OBJ_FOLDER)%.o: $(SOURCE_CODE_FOLDER)%.c
	bash -c "if [ ! -d "$(OBJ_FOLDER)" ]; then mkdir -p $(OBJ_FOLDER); fi" 
	gcc -c $< -o $@

clean: 
	rm -r $(BUILD_FOLDER)

unit_tests: $(UT_OBJ_FOLDER)binary_tree.o $(UT_OBJ_FOLDER)unit_tests.o
	gcc $(UT_OBJ_FOLDER)binary_tree.o $(UT_OBJ_FOLDER)unit_tests.o -o $(UT_BUILD_FOLDER)$(UT_TARGET) $(LIBS)

$(UT_OBJ_FOLDER)binary_tree.o: $(SOURCE_CODE_FOLDER)binary_tree.c
	bash -c "if [ ! -d "$(UT_OBJ_FOLDER)" ]; then mkdir -p $(UT_OBJ_FOLDER); fi"
	gcc -c $(SOURCE_CODE_FOLDER)binary_tree.c -o $(UT_OBJ_FOLDER)binary_tree.o

$(UT_OBJ_FOLDER)unit_tests.o: $(UT_FOLDER)unit_tests.c 
	gcc -c $(UT_FOLDER)unit_tests.c -o $(UT_OBJ_FOLDER)unit_tests.o
