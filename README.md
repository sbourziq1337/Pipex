# What is a Pipe?

* The objective of this C project is to create a program that connects two (or more, for bonus) UNIX commands using pipes. A pipe allows the output of the first command to be passed as input to the second command. For example, the following piped command displays the word count of the output of the `ls` command:

```
ls | wc -l
````

### Key Points:

- **Unidirectional**: A pipe allows data to flow in only one direction — from the first process to the second.
- **File Descriptors**: In C, when you use the `pipe()` function, it returns two file descriptors: `pfd[0]` (read end) and `pfd[1]` (write end). Data written to `pfd[1]` flows into `pfd[0]`, where it can be read by another process.

### Visual Representation:

![](https://miro.medium.com/v2/resize:fit:392/0*hHBvsQOZtPyVsKCO.jpg)

![](https://miro.medium.com/v2/resize:fit:410/0*oeuQDqAxmi3ZOWVV.gif)

### Example Code:
-----------------------------------
* Here’s a simple example of how to use pipes in C to connect two commands (`ls` and `wc -l`):

```
#include <stdio.h>
#include <unistd.h>

int main() {
    int pfd[2];
    pid_t pid;

    pipe(pfd);  // Create the pipe

    pid = fork();  // Create a child process
    if (pid == 0) {
        // Child process: Write to pipe
        close(pfd[0]);  // Close unused read end
        dup2(pfd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        execlp("ls", "ls", NULL);  // Execute ls command
    } else {
        // Parent process: Read from pipe
        close(pfd[1]);  // Close unused write end
        dup2(pfd[0], STDIN_FILENO);  // Redirect stdin from pipe
        execlp("wc", "wc", "-l", NULL);  // Execute wc -l command
    }
    return 0;
}

```

### Bonus: Piping Multiple Commands
-------------------------------------------

* You can pipe multiple commands by chaining pipes together, using `fork()` for each command. This allows you to create complex pipelines with many commands, like this:

```
`cmd1 | cmd2 | cmd3 | cmd4`
```

### Error Handling
-----------------------------------

* Remember to handle errors when creating pipes, forking processes, or executing commands to ensure your program works reliably.