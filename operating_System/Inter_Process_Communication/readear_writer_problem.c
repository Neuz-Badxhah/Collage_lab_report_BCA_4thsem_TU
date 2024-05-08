#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h> // For sleep

// Semaphores for synchronization
sem_t rw_mutex;       // Semaphore to control write access
sem_t mutex;          // Semaphore to control reader count
int reader_count = 0; // Number of active readers

// Function for readers
void *reader(void *arg)
{
    int reader_id = *(int *)arg; // Reader ID
    while (1)
    {
        sem_wait(&mutex); // Lock to update reader count
        reader_count++;   // Increment reader count
        if (reader_count == 1)
        {
            sem_wait(&rw_mutex); // Lock rw_mutex if it's the first reader
        }
        sem_post(&mutex); // Unlock mutex

        // Simulate reading
        printf("Reader %d is reading.\n", reader_id);
        sleep(rand() % 2 + 1); // Simulate reading time

        sem_wait(&mutex); // Lock to update reader count
        reader_count--;   // Decrement reader count
        if (reader_count == 0)
        {
            sem_post(&rw_mutex); // Release rw_mutex if it's the last reader
        }
        sem_post(&mutex); // Unlock mutex

        // Simulate some time between reads
        sleep(rand() % 2 + 1);
    }
    return NULL;
}

// Function for writers
void *writer(void *arg)
{
    int writer_id = *(int *)arg; // Writer ID
    while (1)
    {
        sem_wait(&rw_mutex); // Lock rw_mutex for exclusive write access

        // Simulate writing
        printf("Writer %d is writing.\n", writer_id);
        sleep(rand() % 3 + 1); // Simulate writing time

        sem_post(&rw_mutex); // Release rw_mutex to allow others to access

        // Simulate some time between writes
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

int main()
{
    printf("Readers and Writers Problem\n");
    pthread_t readers[5];                // Array of reader threads
    pthread_t writers[2];                // Array of writer threads
    int reader_ids[5] = {0, 1, 2, 3, 4}; // IDs for readers
    int writer_ids[2] = {0, 1};          // IDs for writers

    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1); // Initially rw_mutex is available
    sem_init(&mutex, 0, 1);    // Initially mutex is available

    // Create reader threads
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads (wait for their completion)
    for (int i = 0; i < 5; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
