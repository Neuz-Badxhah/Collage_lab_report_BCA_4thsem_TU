#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5                            // Number of philosophers
#define LEFT(phil) ((phil) % NUM_PHILOSOPHERS)        // Index of left fork
#define RIGHT(phil) (((phil) + 1) % NUM_PHILOSOPHERS) // Index of right fork

sem_t forks[NUM_PHILOSOPHERS];                     // Array of semaphores for forks
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for output synchronization

// Philosopher function
void *philosopher(void *arg)
{
    int phil_id = *(int *)arg; // Philosopher ID
    while (1)
    {
        // Philosopher is thinking
        printf("Philosopher %d is thinking.\n", phil_id);
        sleep(rand() % 3 + 1); // Simulate thinking time

        // Pick up forks (acquire resources)
        sem_wait(&forks[LEFT(phil_id)]);  // Pick up left fork
        sem_wait(&forks[RIGHT(phil_id)]); // Pick up right fork

        // Philosopher is eating
        pthread_mutex_lock(&mutex); // Lock for output synchronization
        printf("Philosopher %d is eating.\n", phil_id);
        pthread_mutex_unlock(&mutex); // Unlock output synchronization

        sleep(rand() % 3 + 1); // Simulate eating time

        // Put down forks (release resources)
        sem_post(&forks[LEFT(phil_id)]);  // Put down left fork
        sem_post(&forks[RIGHT(phil_id)]); // Put down right fork
    }

    return NULL;
}

int main()
{
    printf("Dining Philosopher Problem\n\n");
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1); // Initially, all forks are available
        philosopher_ids[i] = i;    // Assign philosopher IDs
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&forks[i]);
    }

    return 0;
}
