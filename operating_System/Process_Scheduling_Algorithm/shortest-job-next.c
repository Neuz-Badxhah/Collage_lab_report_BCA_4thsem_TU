#include <stdio.h>

// Structure to represent a process
typedef struct
{
    int id;        // Process ID
    int at;        // Arrival Time
    int bt;        // Burst Time
    int wt;        // Waiting Time
    int tat;       // Turnaround Time
    int completed; // Completion status
} Process;

// Function to sort processes by arrival time
void SortByArrivalTime(Process p[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to find the shortest job that has arrived
int FindShortestJob(Process p[], int n, int currentTime)
{
    int minBurst = -1;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (!p[i].completed && p[i].at <= currentTime)
        {
            if (minBurst == -1 || p[i].bt < minBurst)
            {
                minBurst = p[i].bt;
                index = i;
            }
        }
    }
    return index;
}

// Function to simulate the SJF scheduling algorithm
void SimulateSJF(Process p[], int n)
{
    int currentTime = 0;
    int completedProcesses = 0;
    int totalWT = 0;
    int totalTAT = 0;

    while (completedProcesses < n)
    {
        int index = FindShortestJob(p, n, currentTime);

        if (index == -1)
        {
            currentTime++; // No process has arrived yet
        }
        else
        {
            // Process selected, calculate waiting and turnaround times
            if (currentTime < p[index].at)
            {
                currentTime = p[index].at;
            }
            p[index].wt = currentTime - p[index].at;
            p[index].tat = p[index].wt + p[index].bt;

            totalWT += p[index].wt;
            totalTAT += p[index].tat;

            // Move time forward and mark process as completed
            currentTime += p[index].bt;
            p[index].completed = 1;
            completedProcesses++;
        }
    }

    // Calculate and print average waiting time and turnaround time
    float avgWT = (float)totalWT / n;
    float avgTAT = (float)totalTAT / n;

    // Print process details
    printf("P\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].at,
               p[i].bt,
               p[i].wt,
               p[i].tat);
    }

    printf("Average Waiting Time = %.2f\n", avgWT);
    printf("Average Turnaround Time = %.2f\n\n", avgTAT);
}

int main()
{
    printf("\n\n\t\tShortest Job Next Scheduling Algorithm\n");
    printf("\t\t---------------------------------------\n\n");
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("Enter Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &processes[i].at);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &processes[i].bt);
        processes[i].id = i + 1;
        processes[i].completed = 0;
    }

    // Sort processes by arrival time
    SortByArrivalTime(processes, n);

    // Simulate Shortest Job First scheduling
    SimulateSJF(processes, n);

    return 0;
}
