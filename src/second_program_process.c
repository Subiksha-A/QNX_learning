#include <stdio.h>
#include <unistd.h> //The unistd.h header file in C provides access to the POSIX operating system API. It is defined by the POSIX.1 standard, which is the base of the Single Unix Specification. This header file is available in any POSIX-compliant operating system and compiler, including Unix, Linux, BSD, macOS, and compilers like GCC and LLVM.

int main()
{
    pid_t pid; //maps to the parent process

    printf("Before fork: PID = %d\n", getpid()); //fetch pid value to be mapped to parent

    pid = fork();   // creates child

    if (pid > 0) {
        // Parent process
        printf("Parent process\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process\n");
        printf("Child PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
    }

    return 0;
}
