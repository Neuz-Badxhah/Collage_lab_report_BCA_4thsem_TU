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

// Function to implement SCAN Disk Scheduling algorithm
void SCAN(int arr[], int head, char *direction)
{
    int seek_count = 0;
    int distance, cur_track;
    int left[SIZE], right[SIZE];
    int seek_sequence[2 * SIZE + 1]; // Considering worst case size
    int left_count = 0, right_count = 0, seek_sequence_count = 0;

    // Adding end values which has to be visited before reversing the direction
    if (direction[0] == 'l')
        left[left_count++] = 0;
    else if (direction[0] == 'r')
        right[right_count++] = DISK_SIZE - 1;

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

    // Run the while loop two times, one by one scanning right and left of the head
    for (int r = 0; r < 2; r++)
    {
        if (direction[0] == 'l')
        {
            for (int i = left_count - 1; i >= 0; i--)
            {
                cur_track = left[i];
                seek_sequence[seek_sequence_count++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "right";
        }
        else if (direction[0] == 'r')
        {
            for (int i = 0; i < right_count; i++)
            {
                cur_track = right[i];
                seek_sequence[seek_sequence_count++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "left";
        }
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
    printf("\nSCAN Disk Scheduling Algorithm\n");
    printf("\nTrack:\t");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\nHead Position: %d\n", head);
    char direction[] = "left";

    SCAN(arr, head, direction);

    return 0;
}
