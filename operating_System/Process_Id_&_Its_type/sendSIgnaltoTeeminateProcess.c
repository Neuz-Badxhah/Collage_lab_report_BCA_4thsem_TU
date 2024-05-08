// Send a Signal to Terminate a Process

#include <stdio.h>
#include <unistd.h> // For fork(), getpid(), and sleep()
#include <signal.h> // For kill()

int main()
{
    printf("Send a Signal to Terminate a Process. \n\n");
    pid_t pid = fork(); // Create a new process (child)

    if (pid == -1)
    {
        perror("\nfork failed\n");
        return 1; // Return non-zero to indicate error
    }

    if (pid == 0)
    {
        // Child process, which will sleep for a while
        printf("\n\nChild Process. PID: %d. Sleeping...\n\n", getpid());
        sleep(10); // Sleep for 10 seconds
        printf("\nChild process done.\n");
    }
    else
    {
        // Parent process
        printf("\n\nParent Process. PID: %d. Terminating Child PID: %d in 5 seconds...\n", getpid(), pid);
        sleep(5);           // Wait 5 seconds
        kill(pid, SIGTERM); // Send SIGTERM to child
        printf("\n\nChild process terminated.\n\n");
    }

    return 0;
}
