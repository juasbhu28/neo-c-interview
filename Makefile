# Definir compilador y flags
SRC_DIR=src
LIB_DIR=test_libraries
OUT_DIR=./build
CFLAGS=-Wall -Wextra -pedantic -std=c11 -fPIC

LIB_DL=-ldl

compile_libs:
	@if [ ! -d "$(OUT_DIR)" ]; then mkdir -p $(OUT_DIR); fi
	gcc -shared $(LIB_DIR)/test_lib.c -fPIC -o $(OUT_DIR)/test_lib.so

compile: compile_libs
	gcc $(CFLAGS) $(SRC_DIR)/main.c $(SRC_DIR)/reader.c -o $(OUT_DIR)/test $(LIB_DL)

clean:
	rm -f $(OUT_DIR)/test $(OUT_DIR)/*.so

run:
	./$(OUT_DIR)/test scripts/test_script.sc

.PHONY: clean run compile
