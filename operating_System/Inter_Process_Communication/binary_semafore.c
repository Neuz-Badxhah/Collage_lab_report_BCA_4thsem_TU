#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h> // For sleep

// Shared variables
int shared_resource = 0; // A shared variable representing some resource

// Mutex for mutual exclusion
sem_t mutex; // Binary semaphore to protect the critical section

// Function to simulate critical section
void critical_section(int thread_id)
{
    sem_wait(&mutex); // Lock the mutex to enter the critical section

    // Simulate some critical section work
    printf("Thread %d is entering the critical section.\n", thread_id);
    shared_resource++; // Increment the shared resource
    sleep(1);          // Simulate some work in the critical section
    printf("Thread %d is leaving the critical section. Shared resource: %d\n", thread_id, shared_resource);

    sem_post(&mutex); // Unlock the mutex to leave the critical section
}

// Thread function
void *thread_func(void *arg)
{
    int thread_id = *(int *)arg; // Thread ID

    for (int i = 0; i < 3; i++)
    { // Each thread enters the critical section three times
        critical_section(thread_id);

        // Simulate some work outside the critical section
        sleep(rand() % 3); // Random sleep to simulate different processing times
    }

    return NULL;
}

int main()
{
    printf("Binary Semaphore\n");
    pthread_t t1, t2;           // Two threads
    int thread_ids[2] = {0, 1}; // Thread IDs

    // Initialize the mutex
    sem_init(&mutex, 0, 1); // Binary semaphore initialized to 1 (unlocked)

    // Create two threads
    pthread_create(&t1, NULL, thread_func, &thread_ids[0]);
    pthread_create(&t2, NULL, thread_func, &thread_ids[1]);

    // Join threads (wait for their completion)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Clean up the mutex
    sem_destroy(&mutex);

    return 0;
}
