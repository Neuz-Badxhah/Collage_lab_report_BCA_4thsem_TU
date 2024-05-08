#include <stdio.h>
#include <stdlib.h>

// Calculates difference of each track number with the head position
void calculatedifference(int request[], int head, int diff[][2], int n)
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = abs(head - request[i]);
    }
}

// Find unaccessed track which is at minimum distance from head
int findMIN(int diff[][2], int n)
{
    int index = -1;
    int minimum = 1e9;

    for (int i = 0; i < n; i++)
    {
        if (!diff[i][1] && minimum > diff[i][0])
        {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}

void shortestSeekTimeFirst(int request[], int head, int n)
{
    if (n == 0)
    {
        return;
    }

    int diff[n][2]; // Initialize the difference array
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = 0;
        diff[i][1] = 0;
    }

    int seekcount = 0;       // Count total number of seek operations
    int seeksequence[n + 1]; // Stores sequence in which disk access is done

    for (int i = 0; i < n; i++)
    {
        seeksequence[i] = head;
        calculatedifference(request, head, diff, n);
        int index = findMIN(diff, n);
        diff[index][1] = 1;

        seekcount += diff[index][0]; // Increase the total count
        head = request[index];       // Accessed track is now new head
    }
    seeksequence[n] = head;

    printf("Total number of seek operations = %d\n", seekcount);
    printf("Seek sequence is: ");

    // Print the sequence
    for (int i = 0; i <= n; i++)
    {
        printf("%d\t", seeksequence[i]);
    }
}

// Driver code
int main()
{
    int n = 8;
    int proc[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int size = sizeof(proc) / sizeof(proc[0]);
    printf("\nShortest Seek Time First\n");
    printf("\nTrack:\t");

    for (int i = 0; i < size; i++)
    {
        printf("%d \t", proc[i]);
    }

    shortestSeekTimeFirst(proc, 50, n);

    return 0;
}
