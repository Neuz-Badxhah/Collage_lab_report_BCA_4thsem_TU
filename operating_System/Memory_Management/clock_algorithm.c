#include <stdio.h>
#include <stdbool.h>

#define FRAME_SIZE 3   // Number of frames in memory
#define REF_STR_LEN 10 // Length of the reference string

typedef struct
{
    int page;           // The page stored in the frame
    bool reference_bit; // Reference bit indicating if the page has been accessed
} Frame;

// Function to find the next frame to replace using the Clock Algorithm
int find_clock_replacement(Frame frames[], int frame_size, int *clock_hand)
{
    while (true)
    {
        // If the reference bit is 0, this frame can be replaced
        if (frames[*clock_hand].reference_bit == false)
        {
            int index = *clock_hand;
            *clock_hand = (*clock_hand + 1) % frame_size; // Move the clock hand
            return index;
        }

        // If the reference bit is 1, give a second chance by setting it to 0
        frames[*clock_hand].reference_bit = false;
        *clock_hand = (*clock_hand + 1) % frame_size; // Move the clock hand
    }
}

// Function to simulate the Clock Algorithm
void clock_page_replacement(int reference_string[], int ref_len)
{
    Frame frames[FRAME_SIZE]; // Array of frames
    int clock_hand = 0;       // The clock hand's starting position
    int page_faults = 0;      // Count of page faults

    // Initialize frames to represent empty slots
    for (int i = 0; i < FRAME_SIZE; i++)
    {
        frames[i].page = -1;
        frames[i].reference_bit = false;
    }

    // Output header for the tabular output
    printf("Step\tPage\tFrames\t\tClock Hand\tFault\n");
    printf("----\t----\t-------\t\t----------\t-----\n");

    // Loop through the reference string and simulate page replacement
    for (int i = 0; i < ref_len; i++)
    {
        int current_page = reference_string[i];
        bool page_found = false;

        // Check if the page is already in a frame
        for (int j = 0; j < FRAME_SIZE; j++)
        {
            if (frames[j].page == current_page)
            {
                frames[j].reference_bit = true; // Set the reference bit
                page_found = true;
                break;
            }
        }

        // If the page is not found, it's a page fault
        if (!page_found)
        {
            page_faults++;

            // Find the frame to replace using the Clock Algorithm
            int replacement_index = find_clock_replacement(frames, FRAME_SIZE, &clock_hand);

            // Replace the page and set the reference bit to true
            frames[replacement_index].page = current_page;
            frames[replacement_index].reference_bit = true;

            printf("%d\t%d\t", i, current_page);
            for (int j = 0; j < FRAME_SIZE; j++)
            {
                if (frames[j].page == -1)
                {
                    printf("N/A ");
                }
                else
                {
                    printf("%d ", frames[j].page);
                }
            }
            printf("\t%d\t\tFault\n", clock_hand);
        }
        else
        {
            // If the page is already in a frame, no page fault
            printf("%d\t%d\t", i, current_page);
            for (int j = 0; j < FRAME_SIZE; j++)
            {
                if (frames[j].page == -1)
                {
                    printf("N/A ");
                }
                else
                {
                    printf("%d ", frames[j].page);
                }
            }
            printf("\t%d\t\tNo Fault\n", clock_hand);
        }
    }

    printf("\nTotal page faults: %d\n", page_faults);
}

int main()
{
    int reference_string[REF_STR_LEN] = {1, 3, 0, 3, 5, 6, 3, 0, 3, 6}; // Example reference string

    clock_page_replacement(reference_string, REF_STR_LEN);

    return 0;
}
