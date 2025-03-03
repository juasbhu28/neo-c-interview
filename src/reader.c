#define _POSIX_C_SOURCE 200112L  /* Indica conformidad con POSIX.1-2001 */

#include "reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <errno.h>
#include <unistd.h>

void *loaded_library = NULL;

void load_library(const char *name) {
  if (loaded_library != NULL) {
    dlclose(loaded_library);
    loaded_library = NULL;
  }

  dlerror(); /* Limpiar cualquier error previo */
  loaded_library = dlopen(name, RTLD_NOW);

  if (loaded_library == NULL) {
    fprintf(stderr, "Error: Could not load library %s: %s\n", name, dlerror());
    exit(EXIT_FAILURE);
  }

  printf("Loaded library: %s\n", name);
}

void call_function(const char *function_name) {
  if (loaded_library == NULL) {
    fprintf(stderr, "Error: No library loaded\n");
    exit(EXIT_FAILURE);
  }

  dlerror(); /* Limpiar cualquier error previo */
  void (*func)(void) = (void (*)(void))dlsym(loaded_library, function_name);
  char *error = dlerror();

  if (error != NULL) {
    fprintf(stderr, "Error: Could not find function %s: %s\n", function_name, error);
    exit(EXIT_FAILURE);
  }

  printf("Function %s executed successfully.\n", function_name);
  func();
}

void execute_script(const char *filename) {
  if (filename == NULL) {
    return;
  }

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error: Could not open file %s: %s\n", filename, strerror(errno));
    return;
  }

  char line[MAX_LINE];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = 0;

    /* Ignorar líneas vacías y comentarios */
    if (line[0] == '#' || line[0] == ';' || line[0] == '\0')
      continue;

    char *command = strtok(line, " ");
    char *arg = strtok(NULL, " ");

    if (command == NULL || arg == NULL) {
      fprintf(stderr, "Warning: Invalid line format: %s\n", line);
      continue;
    }

    if (strcmp(command, "use") == 0) {
      load_library(arg);
      continue;
    }

    if (strcmp(command, "call") == 0) {
      call_function(arg);
      continue;
    }

    fprintf(stderr, "Warning: Unknown command: %s\n", command);
  }

  fclose(file);
  if (loaded_library != NULL) {
    dlclose(loaded_library);
    loaded_library = NULL;
  }
}
