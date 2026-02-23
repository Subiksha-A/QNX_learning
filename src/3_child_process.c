#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>   // Required for wait()

/*
    PROGRAM GOAL:
    -------------
    Create 3 child processes from a single parent process.
    Parent waits for all children to finish before exiting.

    IMPORTANT CONCEPTS:
    -------------------
    fork()  -> creates a new process
    getpid() -> returns current process ID
    getppid() -> returns parent process ID
    wait() -> makes parent wait for child termination

    PROCESS STRUCTURE:
    
        Parent
          ├── Child 1
          ├── Child 2
          └── Child 3
*/

int main() {

    int i;
    pid_t pid;   // Stores return value of fork()

    printf("Parent process ID: %d\n", getpid());
    printf("Starting to create child processes...\n");

    for (i = 0; i < 3; i++) {

        // fork() creates a child process
        pid = fork();

        if (pid < 0) {
            // fork failed
            fprintf(stderr, "fork failed!\n");
            return 1;
        }
        else if (pid == 0) {
            /*
                CHILD PROCESS BLOCK

                fork() returns 0 in the child.
                Each child prints its PID and its parent PID.
            */
            printf("Child process %d created. My PID is %d, Parent PID is %d\n",
                   i + 1, getpid(), getppid());

            /*
                exit(0) is VERY IMPORTANT.

                Without this:
                Child would continue loop
                Child would create more children
                That leads to exponential process creation.
            */
            exit(0);
        }

        /*
            Parent continues loop to create next child.
            Parent receives child PID (>0).
        */
    }

    /*
        PARENT PROCESS BLOCK

        After creating 3 children,
        parent waits for all children to terminate.
    */

    for (i = 0; i < 3; i++) {
        wait(NULL);   // Wait for any child process
    }

    printf("All 3 child processes finished. Parent process exiting.\n");

    return 0;
}
