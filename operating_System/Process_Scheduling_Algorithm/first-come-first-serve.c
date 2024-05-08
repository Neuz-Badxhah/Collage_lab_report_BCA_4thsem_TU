#include <stdio.h>

// Function to calculate waiting time, turnaround time,
// and average waiting time
void CalculateTimes(int at[], int bt[], int N)
{
    // Declare arrays for waiting time and turnaround time
    int wt[N];
    int tat[N];

    // Waiting time for the first process is 0
    wt[0] = 0;

    // Calculating waiting time for each process from the given formula
    for (int i = 1; i < N; i++)
    {
        // Waiting time = (previous arrival time + previous burst time + previous waiting time) - current arrival time
        wt[i] = (at[i - 1] + bt[i - 1] + wt[i - 1]) - at[i];
        if (wt[i] < 0)
        {
            wt[i] = 0; // Ensure waiting time doesn't go negative
        }
    }

    // Calculating turnaround time for each process
    for (int i = 0; i < N; i++)
    {
        tat[i] = bt[i] + wt[i];
    }

    printf("\n\n\t\tFirst-Come, First-Served\n");
    printf("\t\t........................\n\n");
    printf("PN\t\tAT\t\tBT\t\tWT\t\tTAT\n\n");

    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    // Print the details for each process and calculate totals
    for (int i = 0; i < N; i++)
    {
        totalWaitingTime += wt[i];
        totalTurnaroundTime += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    // Calculate the average waiting time and turnaround time
    float averageWaitingTime = totalWaitingTime / N;
    float averageTurnaroundTime = totalTurnaroundTime / N;

    // Print the average waiting time and turnaround time
    printf("\nAverage waiting time = %.2f\n", averageWaitingTime);
    printf("Average turnaround time = %.2f\n\n", averageTurnaroundTime);
}

// Driver code
int main()
{
    // Number of processes
    int N = 4; // Corrected to match the number of elements in the arrays

    // Array for Arrival time
    int at[] = {0, 1, 2, 3};

    // Array for Burst Time
    int bt[] = {5, 3, 7, 4};

    // Function call to find waiting time and turnaround time
    CalculateTimes(at, bt, N);

    return 0;
}
