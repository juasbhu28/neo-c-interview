# Scripting Language Interpreter

## Description

This project implements a scripting language interpreter for testing shared function libraries in C. The application runs as a console application on the GNU/Linux OS (x86 architecture) using the POSIX.1-2001 API.

## Features

- Load shared libraries using the `use <so_name>` command.
- Call exported functions in libraries with the `call <func_name>` command.
- Handles syntax and execution errors gracefully.
- Additional support for comments (`#`, `;`) and line breaks (`\`).
- Interactive mode for direct command input from the terminal.

## Usage Example

### Running the application

```bash
./sotest test.sc
```

### Example script (test.sc)

```terminal
use test.so
call example
call test1_func
use other.so
call func1
```

### Expected output example

```bash
Loaded library: test.so
Function example executed successfully.
Function test1_func executed successfully.
Loaded library: other.so
Function func1 executed successfully.
```

## Compilation

To compile the application, run:

```bash
make
```

or manually:

```bash
gcc -o sotest main.c -ldl
```

## Project Structure

```bash
.
├── doc                # Project requirements
├── src                # Interpreter source code
├── test_libraries     # Shared libraries for testing
├── scripts            # Example scripts (.sc)
├── Makefile           # Build instructions
├── .gitignore         # Git ignore file
├── .pre-commit.yaml   # Pre-commit hooks
└── README.md          # Project documentation


```

## Testing & Self-Verification

Run the included test script:

```bash
./sotest scripts/test.sc
```

Check the console output to ensure all functions execute correctly.

## Notes

- Syntax errors generate warnings without stopping the script execution.
- Command execution errors terminate the script execution.

## Author

Developed by juasbhu28
