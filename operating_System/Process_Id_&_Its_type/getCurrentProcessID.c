// Get the Current Process ID
#include <stdio.h>
#include <unistd.h> // For getpid()

int main()
{
    pid_t pid = getpid(); // Get the current process ID
    printf("\n\nGet the Current Process ID. \n\n");
    printf("Current Process ID: %d\n\n\n", pid);
    return 0;
}
