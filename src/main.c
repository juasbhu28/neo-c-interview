#define _POSIX_C_SOURCE 200112L  /* Indica conformidad con POSIX.1-2001 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "reader.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <script>\n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Verificar que el archivo existe y es accesible */
  if (access(argv[1], R_OK) != 0) {
    fprintf(stderr, "Error: Cannot access script file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  execute_script(argv[1]);

  return EXIT_SUCCESS;
}
