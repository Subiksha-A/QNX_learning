#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // fork(), sleep()
#include <signal.h>     // kill(), SIGKILL
#include <sys/wait.h>   // wait()

/*
    PROGRAM GOAL:
    -------------
    Parent creates a child.
    Child runs infinitely.
    Parent waits 4 seconds.
    Parent kills child using SIGKILL.

    PROCESS LIFECYCLE:
    ------------------
    1. fork()
    2. Child runs infinite loop
    3. Parent waits 4 seconds
    4. Parent sends SIGKILL
    5. Kernel terminates child
    6. Parent collects child using wait()

*/

int main() {

    pid_t pid = fork();   // Create child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // CHILD PROCESS
        while (1) {
            printf("Child process running....\n");
            sleep(1);  // Pause execution for 1 second
        }
    }
    else {
        // PARENT PROCESS
        sleep(4);  // Allow child to run for 4 seconds

        printf("Parent sending SIGKILL to child...\n");

        kill(pid, SIGKILL);  // Send kill signal  
        

        /* What happens inside when you call sigkill?
          Kernel marks process state as "Terminated"
          Scheduler removes it from run queue
          Memory released
          Exit code stored
          Parent notified
          wait() collects status
        */

        wait(NULL);  // Collect child to prevent zombie

        printf("Child terminated by parent\n");
    }

    return 0;
}
