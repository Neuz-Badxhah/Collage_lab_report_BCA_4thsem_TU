#include <stdio.h>

// Process structure to represent a process
struct Process
{
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
};

// Function to swap two processes
void swap(struct Process *xp, struct Process *yp)
{
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to sort processes by burst time (in descending order)
void bubbleSort(struct Process proc[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // If the current burst time is smaller than the next, swap
            if (proc[j].bt < proc[j + 1].bt)
            {
                swap(&proc[j], &proc[j + 1]);
            }
        }
    }
}

// Function to calculate waiting time and turnaround time
void findAvgTime(struct Process proc[], int n)
{
    bubbleSort(proc, n); // Sort processes by burst time (LJF)
    int wt[n];           // Waiting Time
    int tat[n];          // Turnaround Time
    int total_wt = 0;    // Total Waiting Time
    int total_tat = 0;   // Total Turnaround Time

    // Waiting time for the first process is based on its arrival time
    wt[0] = 0;
    tat[0] = proc[0].bt;

    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + proc[i - 1].bt - proc[i].art + proc[i - 1].art;
        if (wt[i] < 0)
        {
            wt[i] = 0; // Ensure waiting time doesn't go negative
        }
        tat[i] = wt[i] + proc[i].bt;
    }

    printf("\t\tLongest Job First\n");
    printf("\t\t......................\n\n");
    // Display processes along with details
    printf(" P\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].art, proc[i].bt, wt[i], tat[i]);
    }

    // Display average waiting time and average turnaround time
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main()
{
    struct Process proc[] = {
        {1, 3, 0}, // P1 with burst time 3, arrival time 0
        {2, 6, 1}, // P2 with burst time 6, arrival time 1
        {3, 2, 2}, // P3 with burst time 2, arrival time 2
        {4, 8, 3}, // P4 with burst time 8, arrival time 3
    };

    int n = sizeof(proc) / sizeof(proc[0]);

    findAvgTime(proc, n);
    return 0;
}
