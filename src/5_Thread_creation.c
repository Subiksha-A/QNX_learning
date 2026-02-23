/*
Concept mapping with scenario:

Car ECU (process)
├── Sensor-reading thread
├── Control algorithm thread
├── Actuator control thread

Threads allow:
- Parallel sensor reading
- Real-time threshold checking
- Non-blocking control
*/

#include <stdio.h>
#include <pthread.h>

/*
    POSIX THREAD (PTHREAD) PROGRAM

    Goal:
    -----
    Create a thread (lightweight execution unit)
    inside a single process.

    Important:
    Threads are NOT separate processes.
    They share the same memory space.
*/

// Thread function
// Must return void* and accept void* argument (POSIX standard format)
void* thread_func(void* arg)
{
    printf("Hello from thread!\n");

    /*
        This is a worker thread.
        It runs concurrently with main thread.

        It shares:
        - Global variables
        - Heap memory
        - File descriptors

        It has its own:
        - Stack
        - Registers
        - Program counter
    */

    return NULL;  // Thread exits here
}

int main()
{
    pthread_t tid;  // Thread ID (NOT process ID)

    /*
        Main function runs as the initial thread of the process.
        This is called the "main thread".

        When we create another thread,
        it becomes a peer thread inside same process.
    */

    // Create thread
    pthread_create(&tid, NULL, thread_func, NULL);
    /*
        Arguments:
        &tid  -> address to store thread ID
        NULL  -> default thread attributes
        thread_func -> function executed by thread
        NULL  -> argument passed to thread function
    */

    // Wait for thread to finish execution
    pthread_join(tid, NULL);
    /*
        pthread_join blocks main thread
        until the created thread completes.

        Without join:
        main may exit early,
        terminating entire process.
    */

    printf("Main thread exiting\n");

    return 0;
}
