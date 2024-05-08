#include <stdio.h>
#include <stdbool.h>

// Structure representing a process
typedef struct
{
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int priority;   // Priority
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int ct;         // Completion Time
    int rt;         // Remaining Time
    bool completed; // Completion status
} Process;

// Function to find the process with the highest priority (smallest priority number)
int findHighestPriorityProcess(Process proc[], int n, int currentTime)
{
    int highestPriority = -1;
    int index = -1;

    for (int i = 0; i < n; i++)
    {
        if (!proc[i].completed && proc[i].at <= currentTime)
        {
            if (highestPriority == -1 || proc[i].priority < highestPriority)
            {
                highestPriority = proc[i].priority;
                index = i;
            }
        }
    }

    return index; // Return the index of the process with the highest priority
}

// Function to simulate priority scheduling
void simulatePriorityScheduling(Process proc[], int n)
{
    int currentTime = 0;        // Current simulation time
    int completedProcesses = 0; // Counter for completed processes

    while (completedProcesses < n)
    {
        int index = findHighestPriorityProcess(proc, n, currentTime);

        if (index == -1)
        {                  // If no process is available at current time
            currentTime++; // CPU is idle
        }
        else
        {
            // Process found, start it
            Process *currentProcess = &proc[index];

            // Compute waiting time and start executing the process
            if (currentProcess->completed == false)
            {
                // Calculate waiting time if the process starts for the first time
                if (currentTime < currentProcess->at)
                {
                    currentTime = currentProcess->at; // Ensure current time is not before arrival
                }

                currentProcess->wt = currentTime - currentProcess->at;         // Waiting time
                currentProcess->ct = currentTime + currentProcess->bt;         // Completion time
                currentProcess->tat = currentProcess->ct - currentProcess->at; // Turnaround time

                // Move the time forward by the burst time
                currentTime += currentProcess->bt;

                // Mark the process as completed
                currentProcess->completed = true;
                completedProcesses++;
            }
        }
    }
}

// Function to calculate and display average waiting and turnaround times
void displayResults(Process proc[], int n)
{
    float totalWT = 0, totalTAT = 0;

    printf("Process\tAT\tBT\tPriority\tWT\tTAT\tCT\n");

    // Calculate total waiting time and turnaround time
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid,
               proc[i].at,
               proc[i].bt,
               proc[i].priority,
               proc[i].wt,
               proc[i].tat,
               proc[i].ct);

        totalWT += proc[i].wt;
        totalTAT += proc[i].tat;
    }

    // Display average waiting time and turnaround time
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

int main()
{
    printf("\n\n\t\t Priority Scheduling\n\n");
    printf("\t\t......................\n\n");
    // Process details with Process ID, Arrival Time, Burst Time, and Priority
    Process proc[] = {
        {1, 0, 7, 2, 0, 0, 0, 7, false},
        {2, 1, 4, 1, 0, 0, 0, 4, false},
        {3, 2, 5, 3, 0, 0, 0, 5, false},
        {4, 3, 6, 1, 0, 0, 0, 6, false},
    };

    int n = sizeof(proc) / sizeof(proc[0]);

    simulatePriorityScheduling(proc, n); // Simulate priority-based scheduling
    displayResults(proc, n);             // Display results with average waiting time and turnaround time

    return 0;
}
