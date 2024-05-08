#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 // Number of frames in memory
#define MAX_PAGES 10 // Maximum number of page references

// Function to check if a page is already in frames
int is_page_in_frames(int frames[], int frame_count, int page)
{
    for (int i = 0; i < frame_count; i++)
    {
        if (frames[i] == page)
        {
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

// FIFO Page Replacement Algorithm
void fifo_page_replacement(int page_references[], int page_count, int frame_count)
{
    int frames[frame_count];
    int frame_pointer = 0;

    // Initialize frames to be empty
    for (int i = 0; i < frame_count; i++)
    {
        frames[i] = -1;
    }

    printf("FIFO Page Replacement\n");
    printf("---------------------\n");
    for (int i = 0; i < page_count; i++)
    {
        int page = page_references[i];

        if (!is_page_in_frames(frames, frame_count, page))
        {
            // Page is not in frames; replace the oldest frame
            frames[frame_pointer] = page;
            frame_pointer = (frame_pointer + 1) % frame_count; // Move to the next frame
            printf("Page %d caused a page fault. ", page);
            print_frames(frames, frame_count);
        }
        else
        {
            printf("Page %d is already in frames. ", page);
            print_frames(frames, frame_count);
        }
    }
    printf("\n");
}

int main()
{
    int page_references[MAX_PAGES] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int page_count = 12; // Number of page references

    fifo_page_replacement(page_references, page_count, MAX_FRAMES);

    return 0;
}
