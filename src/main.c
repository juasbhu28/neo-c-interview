#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#define MAX_LINE 256

void *loaded_library = NULL;

void process_command(char *line);
void load_library(const char *name);
void call_function(const char *function_name);

int main(int argc, char *argv[]) {
  printf("Starting script interpreter\n");
  if (argc < 2) {
    printf("Usage: %s <script>\n", argv[0]);
    return 1;
  }

  // open the script file
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    printf("Error: Could not open file %s\n", argv[1]);
    return 1;
  }

  char line[MAX_LINE];
  while (fgets(line, sizeof(line), file)) { //fgets lee una linea del archivo
    line[strcspn(line, "\n")] = 0; //strcspn es una funcion que busca el primer caracter que no es parte de la cadena de caracteres
    printf("Executing line: %s\n", line);
    process_command(line);
  }

  // Close the file
  fclose(file);
  return 0;
}

void process_command(char *line) {
  char *command = strtok(line, " "); //strtok es una funcion que divide una cadena en tokens

  if (!command) return;

  char *arg = strtok(NULL, " ");

  if (!arg) {
    printf("Error: No argument provided for command %s\n", command);
    return;
  }

  if (strcmp(command, "use") == 0) { // strcmp es una funcion que compara dos cadenas
    printf("Using library: %s\n", arg);
    load_library(arg);
    return;
  }

  if (strcmp(command, "call") == 0) {
    printf("Calling function: %s\n", arg);
    call_function(arg);
    return;
  }

  printf("Unknown command: %s\n", command);
}

void load_library(const char *name) {
  if (loaded_library) {
    dlclose(loaded_library);
    loaded_library = NULL;
  }

  loaded_library = dlopen(name, RTLD_NOW);
  if (!loaded_library) {
    printf("Error: Could not load library %s\n", name);
    return;
  }

  printf("Library %s loaded successfully\n", name);
}

void call_function(const char *function_name) {
  if (!loaded_library) {
    printf("Error: No library loaded\n");
    exit(EXIT_FAILURE);
  }

  void (*function)(void) = dlsym(loaded_library, function_name);
  char *error = dlerror();
  if (error) {
    printf("Error: Could not find function %s: %s\n", function_name, error);
    exit(EXIT_FAILURE);
  }

  function(); // llama a la funcion, funcion es un puntero a la funcion

  printf("Function %s called successfully\n", function_name);
}
