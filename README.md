# 42sv_minishell

:building_construction: **In process** &nbsp; ![yellow](https://img.icons8.com/emoji/24/000000/yellow-circle-emoji.png)

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)

The objective of this project is to create a simple shell and learn about processes and file descriptors.

*The project is written in accordance with the school's [Norm](https://github.com/akovalyo/DOCS/blob/master/42_NORM.md).*

### Allowed functions

|   Function     |  Description    |
| ---    | --- |
| **malloc** |     |
| **free**   |     |
| **write** | |
| **open** ||
| **read** ||
| **close** | |
| **[fork](https://linux.die.net/man/3/fork)** | **#include <unistd.h>** <p></p> pid_t fork(void) <p></p> Creates a new process by duplicating the calling process. <p></p>**Returns** a value of 0 to the child process and returns the process ID of the child process to the parent process.  Otherwise, a value of -1 is returned to the parent process, no child process is created, and the global variable errno is set to indicate the error.|
| **[wait](https://man7.org/linux/man-pages/man2/wait.2.html)**<p></p>**waitpid**|pid_t wait(int *wstatus);<p></p>pid_t waitpid(pid_t pid, int *wstatus, int options); <p></p> Used to wait for state changes in a child of the calling process, and obtain information about the child whose state has changed. <p></p>The **wait()** system call suspends execution of the calling thread until one of its children terminates.<p></p>The **waitpid()** system call suspends execution of the calling thread until a child specified by pid argument has changed state. |
| **[wait3, wait4](https://www.man7.org/linux/man-pages/man2/wait3.2.html)**| pid_t wait3(int *wstatus, int options, struct rusage *rusage); <p></p>pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);<p></p>The **wait3()** and **wait4()** system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage. |
| **[signal](https://www.freebsd.org/cgi/man.cgi?query=signal&sektion=3&manpath=freebsd-release-ports)**|**#include <signal.h>**<p></p>sig_t signal(int	sig, sig_t func);|
|**[kill](https://linux.die.net/man/3/kill)**|**#include <signal.h>**<p></p>int kill(pid_t pid, int sig);|
|**[exit](https://www.man7.org/linux/man-pages/man3/exit.3.html)**| **#include <stdlib.h>**<p></p>void exit(int status);<p></p>The exit() function causes normal process termination and the least significant byte of status (i.e., status & 0xFF) is returned to the parent|
|**[getcwd](https://linux.die.net/man/3/getcwd)**| **#include <unistd.h>**<p></p>char *getcwd(char *buf, size_t size);<p></p>Copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size.|
|**[chdir](https://linux.die.net/man/3/chdir)**| **#include <unistd.h>**<p></p>int chdir(const char *path);<p></p>The chdir() function shall cause the directory named by the pathname pointed to by the path argument to become the current working directory; that is, the starting point for path searches for pathnames not beginning with '/' .|
|**[stat](https://linux.die.net/man/3/stat)**| **#include <sys/stat.h>**<p></p>int stat(const char *restrict path, struct stat *restrict buf);<p></p>The stat() function shall obtain information about the named file and write it to the area pointed to by the buf argument. The path argument points to a pathname naming a file. Read, write, or execute permission of the named file is not required. An implementation that provides additional or alternate file access control mechanisms may, under implementation-defined conditions, cause stat() to fail. In particular, the system may deny the existence of the file specified by path.|
|**[lstat](https://linux.die.net/man/3/lstat)**| **#include <sys/stat.h>**<p></p>int lstat(const char *restrict path, struct stat *restrict buf);<p></p>The lstat() function shall be equivalent to stat(), except when path refers to a symbolic link. In that case lstat() shall return information about the link, while stat() shall return information about the file the link references.|
|**[fstat](https://linux.die.net/man/3/fstat)**| **#include <sys/stat.h>**<p></p>int fstat(int fildes, struct stat *buf);<p></p>The fstat() function shall obtain information about an open file associated with the file descriptor fildes, and shall write it to the area pointed to by buf.|
|**[execve](https://linux.die.net/man/3/execve)**| **#include <unistd.h>**<p></p>int execve(const char *path, char *const argv[], char *const envp[]);<p></p>Executes a file|
|**[dup, dup2](https://linux.die.net/man/3/dup)**| **#include <unistd.h>**<p></p>int dup(int fildes);<p></p>int dup2(int fildes, int fildes2);<p></p>Duplicates an open file descriptor|
|**[pipe](https://linux.die.net/man/3/pipe)**| **#include <unistd.h>**<p></p>int pipe(int fildes[2]);<p></p>Creates an interprocess channel|
|**[opendir](https://man7.org/linux/man-pages/man3/opendir.3.html)**| **#include <sys/types.h>**<p></p>**#include <dirent.h>**<p></p>DIR *opendir(const char *name);<p></p>Opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.  The stream is positioned at the first entry in the directory.|
|**[readdir](https://www.man7.org/linux/man-pages/man3/readdir.3.html)**| **#include <dirent.h>**<p></p>struct dirent *readdir(DIR *dirp);<p></p>Returns a pointer to a *dirent* structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching the end of the directory stream or if an error occurred.|
|**[closedir](https://man7.org/linux/man-pages/man3/closedir.3p.html)**| **#include <dirent.h>**<p></p>int closedir(DIR *dirp);<p></p>Closes the directory stream referred to by the argument dirp.  Upon return, the value of dirp may no longer point to an accessible object of the type DIR.  If a file descriptor is used to implement type DIR, that file descriptor shall be closed.|
|**[strerror](https://man7.org/linux/man-pages/man3/strerror.3.html)**| **#include <string.h>**<p></p>char *strerror(int errnum);<p></p>Returns a pointer to a string that describes the error code passed in the argument *errnum*.|
|**[errno](https://man7.org/linux/man-pages/man3/errno.3.html)**| **#include <errno.h>**<p></p>Number of last error|

### Signal

* **Ctrl-C** sends an INT signal ("interrupt", SIGINT); by default, this causes the process to terminate.

* **Ctrl-Z** sends a TSTP signal ("terminal stop", SIGTSTP); by default, this causes the process to suspend execution.

* **Ctrl-\\** sends a QUIT signal (SIGQUIT); by default, this causes the process to terminate and dump core.

### Stat

#### The stat structure

```
struct stat {
    dev_t           st_dev;         /* ID of device containing file */
    ino_t           st_ino;         /* Inode number */
    mode_t          st_mode;        /* File type and mode */
    nlink_t         st_nlink;       /* Number of hard links */
    uid_t           st_uid;         /* User ID of owner */
    gid_t           st_gid;         /* Group ID of owner */
    dev_t           st_rdev;        /* Device ID (if special file) */
    off_t           st_size;        /* Total size, in bytes */
    blksize_t       st_blksize;     /* Block size for filesystem I/O */
    blkcnt_t        st_blocks;      /* Number of 512B blocks allocated */
    struct timespec st_atim;        /* Time of last access */
    struct timespec st_mtim;        /* Time of last modification */
    struct timespec st_ctim;        /* Time of last status change */
    };
```