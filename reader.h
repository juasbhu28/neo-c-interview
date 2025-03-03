#ifndef READER_H
#define READER_H

#define MAX_LINE 1024

/*
 * Executes commands from a script file.
 * The script can load dynamic libraries and call functions from them.
 */
void execute_script(const char *filename);

#endif /* READER_H */
