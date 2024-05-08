#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h> // For sleep

#define N 10 // Number of iterations in critical section

// Flags for indicating the desire to enter the critical section
bool flag[2] = {false, false};

// The turn variable
int turn = 0;

// The critical section
void critical_section(int thread_id)
{
    printf("Thread %d is entering the critical section.\n", thread_id);
    // Simulate critical section work with sleep
    sleep(1);
    printf("Thread %d is leaving the critical section.\n", thread_id);
}

// Function for the first thread
void *thread1(void *arg)
{
    for (int i = 0; i < N; i++)
    {
        flag[0] = true;
        while (flag[1])
        {
            if (turn != 0)
            {
                flag[0] = false;
                while (turn != 0)
                    ; // Busy-wait
                flag[0] = true;
            }
        }
        critical_section(0); // Critical section work
        turn = 1;            // Give turn to the other process
        flag[0] = false;
    }
    return NULL;
}

// Function for the second thread
void *thread2(void *arg)
{
    for (int i = 0; i < N; i++)
    {
        flag[1] = true;
        while (flag[0])
        {
            if (turn != 1)
            {
                flag[1] = false;
                while (turn != 1)
                    ; // Busy-wait
                flag[1] = true;
            }
        }
        critical_section(1); // Critical section work
        turn = 0;            // Give turn to the other process
        flag[1] = false;
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    // Create two threads
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    // Join threads to wait for their completion
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
