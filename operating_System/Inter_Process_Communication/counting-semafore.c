#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep

#define BUFFER_SIZE 5 // Size of the shared buffer

// Shared buffer and indexes for producer-consumer
int buffer[BUFFER_SIZE];
int in = 0;  // Index for producer
int out = 0; // Index for consumer

// Semaphores for synchronization
sem_t mutex; // Binary semaphore for mutual exclusion
sem_t empty; // Counting semaphore for empty slots in the buffer
sem_t full;  // Counting semaphore for filled slots in the buffer

// Producer function
void *producer(void *arg)
{
    int item;
    while (1)
    {
        item = rand() % 100; // Produce a random item
        sem_wait(&empty);    // Wait for an empty slot
        sem_wait(&mutex);    // Acquire mutual exclusion

        // Add item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        printf("Produced: %d\n", item);

        sem_post(&mutex); // Release mutual exclusion
        sem_post(&full);  // Signal that a new item is available

        // Simulate production time
        sleep(rand() % 2);
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full);  // Wait for a filled slot
        sem_wait(&mutex); // Acquire mutual exclusion

        // Remove item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        printf("Consumed: %d\n", item);

        sem_post(&mutex); // Release mutual exclusion
        sem_post(&empty); // Signal that an empty slot is available

        // Simulate consumption time
        sleep(rand() % 3);
    }
    return NULL;
}

int main()
{

    printf("Producer-consumer problem\n\n");
    pthread_t producer_thread;
    pthread_t consumer_thread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);           // Binary semaphore for mutual exclusion
    sem_init(&empty, 0, BUFFER_SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0);            // Initially no filled slots

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads (wait for their completion)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
