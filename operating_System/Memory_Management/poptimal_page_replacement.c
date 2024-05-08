#include <stdio.h>
#include <stdbool.h>

#define FRAME_SIZE 3   // Number of frames in memory
#define NUM_PAGES 8    // Total number of unique pages
#define REF_STR_LEN 10 // Length of the reference string

// Function to check if a page is in the frame
bool is_page_in_frame(int frame[], int page)
{
    for (int i = 0; i < FRAME_SIZE; i++)
    {
        if (frame[i] == page)
        {
            return true;
        }
    }
    return false;
}

// Function to find the optimal page to replace
int find_optimal_page(int frame[], int reference_string[], int ref_len, int current_index)
{
    int furthest_index = -1;
    int page_to_replace = -1;

    for (int i = 0; i < FRAME_SIZE; i++)
    {
        int page = frame[i];
        bool found = false;
        // Find the next use of this page in the reference string
        for (int j = current_index + 1; j < ref_len; j++)
        {
            if (reference_string[j] == page)
            {
                if (j > furthest_index)
                {
                    furthest_index = j;
                    page_to_replace = i;
                }
                found = true;
                break;
            }
        }
        // If a page is never used again, it is the optimal page to replace
        if (!found)
        {
            return i;
        }
    }

    return page_to_replace;
}

// Function to simulate the optimal page replacement algorithm
void optimal_page_replacement(int reference_string[], int ref_len)
{
    int frame[FRAME_SIZE] = {-1, -1, -1}; // Initialize frames to -1 (empty)
    int page_faults = 0;                  // Counter for page faults

    // Header for the tabular output
    printf("Step\tPage\tFrames\t\tFault\n");
    printf("----\t----\t-------\t\t-----\n");

    for (int i = 0; i < ref_len; i++)
    {
        int current_page = reference_string[i];

        // Check if the current page is already in the frame
        if (!is_page_in_frame(frame, current_page))
        {
            // Page fault occurs
            page_faults++;

            // Find an empty frame or use the optimal replacement strategy
            int replacement_index = -1;
            for (int j = 0; j < FRAME_SIZE; j++)
            {
                if (frame[j] == -1)
                {
                    replacement_index = j;
                    break;
                }
            }
            if (replacement_index == -1)
            {
                replacement_index = find_optimal_page(frame, reference_string, ref_len, i);
            }

            // Replace the frame
            frame[replacement_index] = current_page;
            printf("%d\t%d\t", i, current_page);
            for (int j = 0; j < FRAME_SIZE; j++)
            {
                if (frame[j] == -1)
                {
                    printf("N/A ");
                }
                else
                {
                    printf("%d ", frame[j]);
                }
            }
            printf("\tFault\n");
        }
        else
        {
            // No page fault
            printf("%d\t%d\t", i, current_page);
            for (int j = 0; j < FRAME_SIZE; j++)
            {
                if (frame[j] == -1)
                {
                    printf("N/A ");
                }
                else
                {
                    printf("%d ", frame[j]);
                }
            }
            printf("\tNo Fault\n");
        }
    }

    printf("\nTotal page faults: %d\n", page_faults);
}

int main()
{
    int reference_string[REF_STR_LEN] = {1, 2, 3, 1, 4, 5, 3, 2, 1, 6}; // Example reference string

    optimal_page_replacement(reference_string, REF_STR_LEN);

    return 0;
}
