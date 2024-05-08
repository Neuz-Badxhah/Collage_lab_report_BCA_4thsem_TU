// Fork a Child Process and Get PIDs

#include <stdio.h>
#include <unistd.h> // For getpid() and fork()

int main()
{
    printf("Fork a Child Process and Get PIDs. \n\n");
    pid_t pid = fork(); // Create a new process (child)

    if (pid == -1)
    {
        perror("fork failed");
        return 1; // Return non-zero to indicate error
    }

    if (pid == 0)
    {
        // This block runs in the child process
        printf("Child Process. PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else
    {
        // This block runs in the parent process
        printf("Parent Process. PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}
