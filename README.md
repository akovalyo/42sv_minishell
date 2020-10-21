# 42sv_minishell

100% :green_circle: 

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)

The objective of this project is to create a simple shell and learn about processes and file descriptors.

## Usage

**Download and Compile:**

```
git clone https://github.com/akovalyo/42sv_minishell minishell
cd minishell
make
```

**Run:**
```
./minishell
```

## Live

[Run minishell online](https://repl.it/join/alibthfq-akovalyo)

## Common Instructions (mandatory part):

* The project must be written in C and in accordance with the school's [Norm](https://github.com/akovalyo/akovalyo/blob/master/42_NORM.md).

* Functions should not quite unexpectedly (segmentation fault, bus error, double free, etc)

* No memory leaks

* **Allowed functions**:
    malloc, free, write, open, read, close, [fork](https://linux.die.net/man/3/fork), [wait](https://man7.org/linux/man-pages/man2/wait.2.html), [wait3, wait4](https://www.man7.org/linux/man-pages/man2/wait3.2.html), [signal](https://www.freebsd.org/cgi/man.cgi?query=signal&sektion=3&manpath=freebsd-release-ports), [kill](https://linux.die.net/man/3/kill), [exit](https://www.man7.org/linux/man-pages/man3/exit.3.html), [getcwd](https://linux.die.net/man/3/getcwd), [chdir](https://linux.die.net/man/3/chdir), [stat](https://linux.die.net/man/3/stat), [fstat](https://linux.die.net/man/3/fstat), [lstat](https://linux.die.net/man/3/lstat), [execve](https://linux.die.net/man/3/execve), [dup, dup2](https://linux.die.net/man/3/dup), [pipe](https://linux.die.net/man/3/pipe), [opendir](https://man7.org/linux/man-pages/man3/opendir.3.html), [readdir](https://www.man7.org/linux/man-pages/man3/readdir.3.html), [closedir](https://man7.org/linux/man-pages/man3/closedir.3p.html), [strerror](https://man7.org/linux/man-pages/man3/strerror.3.html), [errno](https://man7.org/linux/man-pages/man3/errno.3.html), and functions from [libft](https://github.com/akovalyo/42sv_libft)
    
* **Implement the builtins like in bash:** 
    * *echo* with option '-n'
    * *cd* with only a relative or absolute path
    * *pwd* without any options
    * *export* without any options
    * *unset* without any options
    * *env* without any options and any arguments
    * *exit* without any options
    
* Search and launch the right executable (based on the PATH variable or by using relative or absolute path) like in bash

* **;** in the command should separate commands like in bash

*  **’** and **"** should work like in bash except for multiline commands

* Redirections **'<' '>' '>>'** should work like in bash except for file descriptor aggregation

* Pipes **|** should work like in bash

* Environment variables (**$** followed by characters) should work like in bash

* **$?** should work like in bash

* **ctrl-C, ctrl-D and ctrl-\** should have the same result as in bash

