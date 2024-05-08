#include <stdio.h>
#include <stdbool.h>

// Process structure
typedef struct
{
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int rt;         // Remaining Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    bool completed; // Completion status
} Process;

// Function to find the process with the shortest remaining burst time
int findShortestProcess(Process proc[], int n, int currentTime)
{
    int minTime = -1;
    int index = -1;

    for (int i = 0; i < n; i++)
    {
        if (!proc[i].completed && proc[i].at <= currentTime)
        {
            if (minTime == -1 || proc[i].rt < minTime)
            {
                minTime = proc[i].rt;
                index = i;
            }
        }
    }

    return index; // Return the index of the process with the shortest remaining burst time
}

// Function to simulate the SRTN scheduling algorithm
void simulateSRTN(Process proc[], int n)
{
    int currentTime = 0;        // Track the current time
    int completedProcesses = 0; // Count of completed processes

    while (completedProcesses < n)
    {
        int index = findShortestProcess(proc, n, currentTime);

        if (index == -1)
        {                  // No process has arrived
            currentTime++; // Idle time
        }
        else
        {
            proc[index].rt--; // Decrement the remaining time
            currentTime++;    // Advance time

            if (proc[index].rt == 0)
            {                                 // If process is completed
                proc[index].completed = true; // Mark as completed
                completedProcesses++;         // Increment the count of completed processes
                // Calculate turnaround time and waiting time
                proc[index].tat = currentTime - proc[index].at;
                proc[index].wt = proc[index].tat - proc[index].bt;
            }
        }
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAvgTimes(Process proc[], int n)
{
    float totalWT = 0, totalTAT = 0;

    printf("P\tAT\tBT\tWT\tTAT\n");

    // Loop through processes to accumulate total waiting time and turnaround time
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid,
               proc[i].at,
               proc[i].bt,
               proc[i].wt,
               proc[i].tat);

        totalWT += proc[i].wt;
        totalTAT += proc[i].tat;
    }

    float avgWT = totalWT / n;
    float avgTAT = totalTAT / n;

    // Display the average times
    printf("\nAverage Waiting Time = %.2f\n", avgWT);
    printf("Average Turnaround Time = %.2f\n", avgTAT);
}

int main()
{
      printf("\n\n\t\tShortest Remaining Job Next Scheduling Algorithm\n");
    printf("\t\t---------------------------------------\n\n");
    // Example processes with Process ID, Arrival Time, Burst Time
    Process proc[] = {
        {1, 0, 7, 7, 0, 0, false},
        {2, 2, 4, 4, 0, 0, false},
        {3, 4, 1, 1, 0, 0, false},
        {4, 5, 5, 5, 0, 0, false},
    };

    int n = sizeof(proc) / sizeof(proc[0]);

    simulateSRTN(proc, n);      // Simulate SRTN scheduling
    calculateAvgTimes(proc, n); // Calculate and display average times

    return 0;
}
