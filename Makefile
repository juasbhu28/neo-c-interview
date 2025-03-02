# Definir compilador y flags
SRC_DIR=src
LIB_DIR=test_libraries
OUT_DIR=./build

LIB_DL=-ldl

compile_libs:
	gcc -shared $(LIB_DIR)/test_lib.c -fPIC -o $(OUT_DIR)/test_lib.so

compile_all: compile_libs
	gcc $(SRC_DIR)/main.c -o $(OUT_DIR)/test $(LIB_DL)

clean:
	rm -f test *.so

run:
	./$(OUT_DIR)/test scripts/test_script.sc

.PHONY: all clean run compile
