# Minishell

## Project Overview

**Minishell** is a project from the 42 curriculum that aims to recreate a simple Unix shell. The goal is to understand how a shell works by implementing features such as command parsing, execution, environment variable management, redirections, pipelines, and built-in commands. This project helps deepen your understanding of process management, file descriptors, memory management, and user interaction in a Unix environment.

## Project Requirements

The project requires you to:
- Implement a shell that can interpret and execute user commands.
- Support built-in commands like `cd`, `echo`, `pwd`, `export`, `unset`, `env`, and `exit`.
- Handle input/output redirections (`>`, `<`, `>>`, `<<`).
- Support pipelines (`|`) to connect multiple commands.
- Manage environment variables and their expansion (e.g., `$HOME`, `$?`).
- Handle signals (like `Ctrl+C` `Ctrl+D`).
- Manage memory efficiently and avoid leaks.
- Use the GNU Readline library for user input.

## What I Learned

Through this project, I learned:
- How shells parse and execute commands.
- How to manage processes using `fork`, `execve`, and `wait`.
- How to manipulate file descriptors for redirections and pipelines.
- How to handle environment variables and their expansion.
- How to use the Readline library for advanced user input.
- How to handle signals and errors gracefully.
- How to write a Makefile for building a C project.
- How to use Valgrind and suppression files to detect and ignore memory leaks from external libraries.

## File Descriptions
Below is an overview of the main folders and files in this project, along with a brief description of their purpose:
```markdown
minishell/
│
├── .valgrindrc         # Valgrind configuration for memory leak checking
├── Makefile            # Automates building, cleaning, and running the project
├── minishell           # The compiled executable (created after build)
├── readline.supp       # Valgrind suppression file for Readline library leaks
│
├── include/
│   └── minishell.h     # Main header file with all struct and function declarations
│
├── libft/              # Custom implementation of standard C library functions
│   ├── ft_*.c          # Various utility functions (string, memory, list, etc.)
│   └── libft.h         # Header file for libft functions
│
└── srcs/               # All source code for minishell
    ├── builtin/        # Built-in shell command implementations
    │   ├── build_ins_utils.c
    │   ├── build_ins_utils1.c
    │   └── ...         # Source files for built-in commands (cd, echo, export, etc.)
    │
    ├── execute/        # Code for executing commands and handling pipes/redirections
    │   ├── exec_inpipe.c
    │   ├── heredocinp.c
    │   ├── heredocinpipe.c
    │   └── utilsinexec.c
    │
    ├── lexer/          # Lexical analysis: splits user input into tokens
    │   ├── lexer.c
    │   ├── lexer1.c
    │   └── ...         # Lexer helpers
    │
    ├── parser/         # Parsing tokens, building command structures, variable expansion
    │   ├── parser.c
    │   ├── parser1.c
    │   ├── instr.c
    │   ├── instr1.c
    │   └── instr2.c
    │
    ├── signals/        # Signal handling (e.g., Ctrl+C, Ctrl+D)
    │   └── signal.c
    │
    ├── utils/          # Utility functions for memory management, errors, etc.
    │   ├── free.c
    │   ├── free1.c
    │   ├── utils.c
    │   └── utils1.c
    │
    └── main.c          # Entry point of the program, initializes and runs the shell
```

### Folder Descriptions

- **include/**: Contains header files, mainly `minishell.h`, which declares all main structures and function prototypes.
- **libft/**: Your custom C library with re-implemented standard functions for string, memory, and list handling.
- **srcs/builtin/**: Implements built-in shell commands and their helpers.
- **srcs/execute/**: Handles command execution, process creation, pipes, and redirections.
- **srcs/lexer/**: Responsible for lexical analysis (tokenizing user input).
- **srcs/parser/**: Parses tokens, handles variable expansion, and builds command structures.
- **srcs/signals/**: Manages signal handling for interactive shell behavior.
- **srcs/utils/**: General utility functions for memory management, error handling, and other helpers.
- **srcs/main.c**: The main entry point; sets up the shell environment, handles the main loop, and coordinates parsing and execution.

---

This structure keeps the code organized and modular, making it easier to maintain and extend.
### `.valgrindrc`

The `.valgrindrc` file is a configuration file for Valgrind, a tool used to detect memory leaks and memory errors in your program.

This file contains the following options:

- `--leak-check=full`: Tells Valgrind to perform a detailed memory leak check, reporting all memory that was allocated but not freed.
- `--show-leak-kinds=all`: Instructs Valgrind to show all types of memory leaks, including definitely lost, indirectly lost, possibly lost, and still reachable blocks.
- `--suppressions=readline.supp`: Uses the `readline.supp` file to suppress (ignore) memory leaks that are known to occur inside the Readline library, so you can focus on leaks in your own code.

#### How to Use

Valgrind will automatically use `.valgrindrc` if you run it from the directory containing this file.  
To check your program for memory leaks using these settings, run:

```sh
valgrind ./minishell
```

### `Makefile`
The Makefile automates the build process.  
It:
- Compiles all source files and links them into the `minishell` executable.
- Handles dependencies and recompilation when files change.
- Provides targets like `all`, `clean`, `fclean`, and `re`.
- Compiles the custom `libft` library and links it with the project.
- Makes it easy to build, clean, and rebuild the project with simple commands.

### `readline.supp`
This is a Valgrind suppression file.  
It tells Valgrind to ignore memory leaks that are known to occur inside the Readline library, which you cannot fix.  
This helps you focus on memory issues in your own code.

## How to Build and Run

```sh
make
./minishell
```

## How to Test

You can test your shell by running various commands, pipelines, and redirections, such as:

```sh
echo hello | grep h > output.txt
cat < output.txt
export TESTVAR=42
echo $TESTVAR
ls | wc -l
```
