# Recipe for building a Binary Search Tree and unit tests fot it

CC := gcc

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
	$(CC) $(OBJ) -o $(BUILD_FOLDER)$(BUILD_TARGET)

$(OBJ_FOLDER)%.o: $(SOURCE_CODE_FOLDER)%.c
	bash -c "if [ ! -d "$(OBJ_FOLDER)" ]; then mkdir -p $(OBJ_FOLDER); fi" 
	$(CC) -c $< -o $@



unit_tests: $(UT_OBJ_FOLDER)binary_tree.o $(UT_OBJ_FOLDER)unit_tests.o
	$(CC) $(UT_OBJ_FOLDER)binary_tree.o $(UT_OBJ_FOLDER)unit_tests.o -o $(UT_BUILD_FOLDER)$(UT_TARGET) $(LIBS)

$(UT_OBJ_FOLDER)binary_tree.o: $(SOURCE_CODE_FOLDER)binary_tree.c
	bash -c "if [ ! -d "$(UT_OBJ_FOLDER)" ]; then mkdir -p $(UT_OBJ_FOLDER); fi"
	$(CC) -c $(SOURCE_CODE_FOLDER)binary_tree.c -o $(UT_OBJ_FOLDER)binary_tree.o

$(UT_OBJ_FOLDER)unit_tests.o: $(UT_FOLDER)unit_tests.c 
	$(CC) -c $(UT_FOLDER)unit_tests.c -o $(UT_OBJ_FOLDER)unit_tests.o



# Recipe for a static library

LIB_TARGET = lib_bst.a
LIB_BUILD_FOLDER = build/
LIB_OBJ_FOLDER = $(LIB_BUILD_FOLDER)obj3/
LIB_OBJ = $(LIB_OBJ_FOLDER)binary_tree.o $(LIB_OBJ_FOLDER)bst_test.o


build_lib: $(LIB_OBJ)
	ar rcs $(LIB_BUILD_FOLDER)$(LIB_TARGET) $(LIB_OBJ)

$(LIB_OBJ_FOLDER)binary_tree.o: $(SOURCE_CODE_FOLDER)binary_tree.c
	bash -c "if [ ! -d "$(LIB_OBJ_FOLDER)" ]; then mkdir -p $(LIB_OBJ_FOLDER); fi"
	$(CC) -c $(SOURCE_CODE_FOLDER)binary_tree.c -o $(LIB_OBJ_FOLDER)binary_tree.o

$(LIB_OBJ_FOLDER)bst_test.o: $(SOURCE_CODE_FOLDER)bst_test.c 
	$(CC) -c $(SOURCE_CODE_FOLDER)bst_test.c -o $(LIB_OBJ_FOLDER)bst_test.o

build_with_lib: 
	$(CC) -c $(SOURCE_CODE_FOLDER)main.c -o $(LIB_OBJ_FOLDER)main.o
	$(CC) -o $(BUILD_FOLDER)$(BUILD_TARGET) $(LIB_OBJ_FOLDER)main.o -L. $(LIB_BUILD_FOLDER)$(LIB_TARGET)



# Recipe for a dynamic linked library

DLL_TARGET = lib_bst.so
DLL_BUILD_FOLDER = build/
DLL_OBJ_FOLDER = $(DLL_BUILD_FOLDER)obj4/
LIB_PATH = /usr/lib/


build_dll:
	bash -c "if [ ! -d "$(DLL_OBJ_FOLDER)" ]; then mkdir -p $(DLL_OBJ_FOLDER); fi"
	$(CC) -c $(SOURCE_CODE_FOLDER)binary_tree.c $(SOURCE_CODE_FOLDER)bst_test.c -fpic
	$(CC) *.o -shared -o $(DLL_BUILD_FOLDER)$(DLL_TARGET)
	mv *.o $(DLL_OBJ_FOLDER)

build_with_dll:
	sudo cp $(DLL_BUILD_FOLDER)$(DLL_TARGET) $(LIB_PATH)
	$(CC) -c $(SOURCE_CODE_FOLDER)main.c -o $(DLL_OBJ_FOLDER)main.o
	$(CC) -o $(BUILD_FOLDER)$(BUILD_TARGET) $(DLL_OBJ_FOLDER)main.o -L. $(LIB_PATH)$(DLL_TARGET)

clean: 
	rm -r $(BUILD_FOLDER)
	sudo rm $(LIB_PATH)$(DLL_TARGET)
	