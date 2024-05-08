#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h> // For random numbers
#include <unistd.h> // For sleep

#define NUM_CHAIRS 5     // Number of chairs in the waiting room
#define NUM_CUSTOMERS 10 // Total number of customers

// Semaphores for synchronization
sem_t customers;           // Semaphore for waiting customers
sem_t barber_ready;        // Semaphore for barber readiness
sem_t access_chairs;       // Semaphore for mutual exclusion in the waiting room
int waiting_customers = 0; // Number of customers in the waiting room

// Barber function
void *barber(void *arg)
{
    while (1)
    {
        // Wait for customers to be available
        sem_wait(&customers);

        // Lock the waiting room to get a customer
        sem_wait(&access_chairs);
        waiting_customers--;      // Decrease the number of waiting customers
        sem_post(&barber_ready);  // Signal that the barber is ready
        sem_post(&access_chairs); // Release the lock

        // Simulate hair cutting
        printf("Barber is cutting hair.\n");
        sleep(rand() % 3 + 1); // Simulate cutting time
    }

    return NULL;
}

// Customer function
void *customer(void *arg)
{
    int customer_id = *(int *)arg; // Customer ID

    // Lock the waiting room to check for available chairs
    sem_wait(&access_chairs);

    if (waiting_customers < NUM_CHAIRS)
    {
        // There is a chair available
        waiting_customers++; // Increment the number of waiting customers
        printf("Customer %d is waiting.\n", customer_id);
        sem_post(&customers);     // Signal that a customer is waiting
        sem_post(&access_chairs); // Release the lock

        // Wait for the barber to be ready
        sem_wait(&barber_ready);

        printf("Customer %d is getting a haircut.\n", customer_id);
    }
    else
    {
        // No chairs available, customer leaves
        printf("Customer %d is leaving, no available chairs.\n", customer_id);
        sem_post(&access_chairs); // Release the lock
    }

    return NULL;
}

int main()
{
    printf("Sleeping barber problem\n");
    pthread_t barber_thread;
    pthread_t customer_threads[NUM_CUSTOMERS];
    int customer_ids[NUM_CUSTOMERS];

    // Initialize semaphores
    sem_init(&customers, 0, 0);     // Initially no customers
    sem_init(&barber_ready, 0, 0);  // Initially barber is not ready
    sem_init(&access_chairs, 0, 1); // Binary semaphore for waiting room access

    // Create the barber thread
    pthread_create(&barber_thread, NULL, barber, NULL);

    // Create customer threads
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        customer_ids[i] = i; // Assign customer IDs
        pthread_create(&customer_threads[i], NULL, customer, &customer_ids[i]);
        sleep(rand() % 2 + 1); // Simulate customer arrival time
    }

    // Join customer threads
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        pthread_join(customer_threads[i], NULL);
    }

    // Clean up semaphores
    sem_destroy(&customers);
    sem_destroy(&barber_ready);
    sem_destroy(&access_chairs);

    return 0;
}
