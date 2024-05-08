#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 3
#define NUM_RESOURCES 2

// Function to print the current allocation of resources
void print_allocation(int allocation[NUM_PROCESSES][NUM_RESOURCES], const char *label)
{
    printf("%s allocation:\n", label);
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < NUM_RESOURCES; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if a process can proceed with given available resources
bool can_proceed(int need[NUM_PROCESSES][NUM_RESOURCES], int available[NUM_RESOURCES], int process)
{
    for (int j = 0; j < NUM_RESOURCES; j++)
    {
        if (need[process][j] > available[j])
        {
            return false;
        }
    }
    return true;
}

// Deadlock prevention by preempting resources from other processes
void preempt_resources(int allocation[NUM_PROCESSES][NUM_RESOURCES], int need[NUM_PROCESSES][NUM_RESOURCES], int available[NUM_RESOURCES], int process)
{
    printf("Preempting resources for process %d\n", process);
    // Find a process to preempt resources from
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        if (i != process)
        {
            for (int j = 0; j < NUM_RESOURCES; j++)
            {  
                if (allocation[i][j] > 0)
                {
                    available[j] += allocation[i][j]; // Release resources
                    need[i][j] += allocation[i][j];   // Update need
                    allocation[i][j] = 0;             // Clear allocation
                    printf("Preempted resource %d from process %d\n", j, i);
                }
            }
        }
    }
}

int main()
{
      printf("\n\n\t\tDeadlock Dectection Algorithm\n");
    printf("\t\t---------------------------------------\n\n");
    int available[NUM_RESOURCES] = {1, 2}; // Available resources
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1},
        {2, 0},
        {0, 1}}; // Resources allocated to processes
    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {3, 2},
        {2, 2},
        {2, 9}};                            // Maximum resources required by processes
    int need[NUM_PROCESSES][NUM_RESOURCES]; // Resources still needed by processes

    // Calculate need by subtracting allocation from max
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        for (int j = 0; j < NUM_RESOURCES; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display the initial state
    printf("Available resources: ");
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        printf("%d ", available[i]);
    }
    printf("\n");

    print_allocation(allocation, "Current");
    print_allocation(need, "Current needs");

    // Attempt to proceed with preemption if necessary
    int process_to_preempt = -1;

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        if (!can_proceed(need, available, i))
        {
            process_to_preempt = i;
            break;
        }
    }

    if (process_to_preempt >= 0)
    {
        preempt_resources(allocation, need, available, process_to_preempt);
    }

    // Re-check if processes can proceed after preemption
    bool all_can_proceed = true;
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        if (!can_proceed(need, available, i))
        {
            all_can_proceed = false;
            break;
        }
    }

    if (all_can_proceed)
    {
        printf("All processes can now proceed.\n");
    }
    else
    {
        printf("Deadlock prevention unsuccessful. Further action required.\n");
    }

    return 0;
}
