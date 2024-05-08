#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 // Number of frames in memory
#define MAX_PAGES 10 // Maximum number of page references

// Function to find the least recently used frame
int find_lru(int time_stamps[], int frame_count)
{
    int min_time = time_stamps[0];
    int lru_index = 0;
    for (int i = 1; i < frame_count; i++)
    {
        if (time_stamps[i] < min_time)
        {
            min_time = time_stamps[i];
            lru_index = i;
        }
    }
    return lru_index;
}

// Function to check if a page is already in frames
int is_page_in_frames(int frames[], int frame_count, int page, int *index)
{
    for (int i = 0; i < frame_count; i++)
    {
        if (frames[i] == page)
        {
            *index = i;
            return 1; // Page is already in frames
        }
    }
    return 0;
}

// Function to print the frames in tabular format
void print_frames(int frames[], int frame_count)
{
    printf("Frames: ");
    for (int i = 0; i < frame_count; i++)
    {
        if (frames[i] == -1)
        {
            printf("[ ] "); // Empty frame
        }
        else
        {
            printf("[%d] ", frames[i]);
        }
    }
    printf("\n");
}

// LRU Page Replacement Algorithm
void lru_page_replacement(int page_references[], int page_count, int frame_count)
{
    int frames[frame_count];
    int time_stamps[frame_count];
    int current_time = 0;

    // Initialize frames and time stamps
    for (int i = 0; i < frame_count; i++)
    {
        frames[i] = -1;
        time_stamps[i] = 0;
    }

    printf("LRU Page Replacement\n");
    printf("--------------------\n");
    for (int i = 0; i < page_count; i++)
    {
        int page = page_references[i];
        int index = -1;

        if (!is_page_in_frames(frames, frame_count, page, &index))
        {
            // Find the least recently used frame to replace
            int lru_index = find_lru(time_stamps, frame_count);
            frames[lru_index] = page;
            time_stamps[lru_index] = current_time; // Update the time stamp
            printf("Page %d caused a page fault. ", page);
            print_frames(frames, frame_count);
        }
        else
        {
            // Update the time stamp for the accessed frame
            time_stamps[index] = current_time;
            printf("Page %d is already in frames. ", page);
            print_frames(frames, frame_count);
        }

        current_time++;
    }
    printf("\n");
}

int main()
{
    int page_references[MAX_PAGES] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int page_count = 12; // Number of page references

    lru_page_replacement(page_references, page_count, MAX_FRAMES);

    return 0;
}
