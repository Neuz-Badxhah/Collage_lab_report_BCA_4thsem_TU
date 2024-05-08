#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
#define DISK_SIZE 200

// Function to sort an array using bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to implement C-SCAN Disk Scheduling algorithm
void CSCAN(int arr[], int head)
{
    int seek_count = 0;
    int distance, cur_track;
    int left[SIZE + 1], right[SIZE + 1]; // Including end values
    int seek_sequence[2 * SIZE + 2];     // Considering worst case size
    int left_count = 0, right_count = 0, seek_sequence_count = 0;

    // Adding end values which has to be visited before reversing the direction
    left[left_count++] = 0;
    right[right_count++] = DISK_SIZE - 1;

    // Tracks on the left of the head will be serviced when the head comes back to the beginning (left end)
    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i] < head)
            left[left_count++] = arr[i];
        if (arr[i] > head)
            right[right_count++] = arr[i];
    }

    // Sorting left and right arrays
    bubbleSort(left, left_count);
    bubbleSort(right, right_count);

    // First service the requests on the right side of the head
    for (int i = 0; i < right_count; i++)
    {
        cur_track = right[i];
        seek_sequence[seek_sequence_count++] = cur_track;
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    // Once reached the right end, jump to the beginning
    head = 0;
    seek_count += (DISK_SIZE - 1); // Adding seek count for head returning from 199 to 0

    // Now service the requests again which are left
    for (int i = 0; i < left_count; i++)
    {
        cur_track = left[i];
        seek_sequence[seek_sequence_count++] = cur_track;
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    printf("Total number of seek operations = %d\n", seek_count);
    printf("Seek Sequence is: ");

    for (int i = 0; i < seek_sequence_count; i++)
    {
        printf("%d\t", seek_sequence[i]);
    }
}

// Driver code
int main()
{
    int arr[SIZE] = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;

    printf("\nC-SCAN Disk Scheduling\n");
    printf("\nTrack:\t");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\nInitial position of head: %d\n", head);
    CSCAN(arr, head);

    return 0;
}
