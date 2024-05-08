#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h> // For sleep

// Shared variables for Peterson's Algorithm
bool flag[2]; // Indicates if a process wants to enter the critical section
int turn;     // Indicates which process's turn it is to enter the critical section

// Critical section function
void critical_section(int thread_id)
{
    printf("Thread %d is in the critical section.\n", thread_id);
    sleep(1); // Simulate some work in the critical section
    printf("Thread %d is leaving the critical section.\n", thread_id);
}

// Thread function for Peterson's Algorithm
void *thread_func(void *arg)
{
    int thread_id = *(int *)arg; // Thread ID

    for (int i = 0; i < 3; i++)
    {
        // Indicate that the thread wants to enter the critical section
        flag[thread_id] = true;
        turn = 1 - thread_id; // Set the other thread's turn

        // Wait if the other thread wants to enter and it's not our turn
        while (flag[1 - thread_id] && turn == 1 - thread_id)
        {
            // Busy wait
        }

        // Critical section
        critical_section(thread_id);

        // Set the flag to false after leaving the critical section
        flag[thread_id] = false;

        // Simulate some work outside the critical section
        sleep(1);
    }

    return NULL;
}

int main()
{
    printf("Peterson's Algorithm\n");
    pthread_t t1, t2;           // Two threads
    int thread_ids[2] = {0, 1}; // Thread IDs

    // Initialize shared variables
    flag[0] = false;
    flag[1] = false;
    turn = 0; // Initially, let's set the turn to 0

    // Create two threads
    pthread_create(&t1, NULL, thread_func, &thread_ids[0]);
    pthread_create(&t2, NULL, thread_func, &thread_ids[1]);

    // Join threads (wait for their completion)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
