#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h> // For sleep

#define NUM_THREADS 5 // Number of threads
#define ITERATIONS 3  // Number of iterations for each thread

// Shared variables for Bakery Algorithm
bool choosing[NUM_THREADS]; // Array indicating if a thread is choosing a ticket
int ticket[NUM_THREADS];    // Array holding each thread's ticket number

// Find the maximum ticket number in the array
int max_ticket()
{
    int max = 0;
    int i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        if (ticket[i] > max)
        {
            max = ticket[i];
        }
    }
    return max;
}

// Compare ticket numbers, with process IDs as a tiebreaker
bool should_wait(int current, int other)
{
    if (ticket[current] < ticket[other])
    {
        return false; // Current has lower ticket
    }
    if (ticket[current] > ticket[other])
    {
        return true; // Other has lower ticket
    }
    return current > other; // Tiebreaker: higher ID should wait
}

// Critical section function
void critical_section(int thread_id)
{
    printf("Thread %d is entering the critical section.\n", thread_id);
    sleep(1); // Simulate some work in the critical section
    printf("Thread %d is leaving the critical section.\n", thread_id);
}

// Thread function for Lamport's Bakery Algorithm
void *thread_func(void *arg)
{
    int thread_id = *(int *)arg; // Thread ID
    int i;
    for (i = 0; i < ITERATIONS; i++)
    {
        // Choosing ticket
        choosing[thread_id] = true;
        ticket[thread_id] = max_ticket() + 1; // Take the next available ticket
        choosing[thread_id] = false;

        // Wait for all other threads to finish choosing
        int j;
        for (j = 0; j < NUM_THREADS; j++)
        {
            while (choosing[j])
            {
                // Busy wait
            }

            // Wait for threads with smaller tickets
            while (should_wait(thread_id, j))
            {
                // Busy wait
            }
        }

        // Critical section
        critical_section(thread_id);

        // Reset ticket after leaving the critical section
        ticket[thread_id] = 0;
    }

    return NULL;
}

int main()
{
    printf("Lamport's Bakery Algorithm\n");
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize shared variables
    int i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        choosing[i] = false;
        ticket[i] = 0;
        thread_ids[i] = i; // Set thread IDs
    }

    // Create threads

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    // Join threads (wait for their completion)

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}