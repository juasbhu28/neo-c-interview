#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <script>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        printf("Ejecutando línea: %s", line);
    }

    fclose(file);
    return 0;
}
