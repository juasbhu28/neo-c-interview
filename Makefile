# Definir compilador y flags
SRC_DIR=src
LIB_DIR=test_libraries

compile:
	gcc $(SRC_DIR)/main.c -o test

compile_libs:
	gcc -shared -o $(LIB_DIR)/test_lib.so $(LIB_DIR)/test_lib.c -fPIC

clean:
	rm -f test *.so

run:
	./test scripts/test_script.sc

.PHONY: all clean
