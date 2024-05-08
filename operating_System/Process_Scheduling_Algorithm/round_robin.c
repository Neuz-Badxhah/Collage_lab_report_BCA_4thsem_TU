#include <stdio.h>

// Structure to represent a process
typedef struct
{
    int pid; // Process ID
    int bt;  // Burst Time
    int at;  // Arrival Time
    int wt;  // Waiting Time
    int tat; // Turnaround Time
} Process;

// Function to simulate Round Robin scheduling
void findAvgTime(Process processes[], int n, int quantum)
{
    int remaining_time[n];
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = processes[i].bt; // Initialize remaining burst time
    }

    int time = 0;      // Current time
    int completed = 0; // Count of completed processes
    int total_wt = 0;  // Total waiting time
    int total_tat = 0; // Total turnaround time

    // Queue processes in a round-robin manner
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= time && remaining_time[i] > 0)
            {
                if (remaining_time[i] > quantum)
                {
                    // Process has more burst time than the quantum
                    time += quantum;              // Increment current time by quantum
                    remaining_time[i] -= quantum; // Decrement remaining time
                }
                else
                {
                    // Process can be completed within this quantum
                    time += remaining_time[i];
                    remaining_time[i] = 0; // Process is completed
                    completed++;

                    processes[i].tat = time - processes[i].at;            // Turnaround time
                    processes[i].wt = processes[i].tat - processes[i].bt; // Waiting time

                    total_tat += processes[i].tat;
                    total_wt += processes[i].wt;
                }
            }
            else if (processes[i].at > time)
            {
                // If no process is ready to run, increment the time
                time++;
                break;
            }
        }
    }

    // Output the process details with calculated waiting times and turnaround times
    printf("Round Robin Scheduling\n");
    printf("Process\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].at,
               processes[i].bt,
               processes[i].wt,
               processes[i].tat);
    }

    // Display the average waiting time and turnaround time
    printf("Average Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main()
{
    printf("\n\n\t\tRound Robin Scheduling\n");
    printf("\t\t..........................\n\n");
    Process processes[] = {
        {1, 4, 0, 0, 0}, // Process 1, Burst Time 4, Arrival Time 0
        {2, 5, 1, 0, 0}, // Process 2, Burst Time 5, Arrival Time 1
        {3, 6, 2, 0, 0}, // Process 3, Burst Time 6, Arrival Time 2
        {4, 2, 3, 0, 0}  // Process 4, Burst Time 2, Arrival Time 3
    };

    int n = sizeof(processes) / sizeof(processes[0]); // Number of processes
    int quantum = 2;                                  // Time quantum

    findAvgTime(processes, n, quantum);

    return 0;
}
