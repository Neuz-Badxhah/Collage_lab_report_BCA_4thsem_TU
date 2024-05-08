#include <stdio.h>
#include <string.h>
#define MAX_BLOCKS 10

typedef struct
{
    int size;    // Size of the memory block
    int is_free; // 1 if free, 0 if allocated
} Block;

// Function to initialize memory blocks
void initialize_blocks(Block blocks[], int n_blocks)
{
    blocks[0] = (Block){100, 1};
    blocks[1] = (Block){500, 1};
    blocks[2] = (Block){200, 1};
    blocks[3] = (Block){300, 1};
    for (int i = 4; i < n_blocks; i++)
    {
        blocks[i] = (Block){0, 0}; // Empty blocks
    }
}

// Function to print the current state of memory blocks
void print_blocks(Block blocks[], int n_blocks)
{
    printf("Index\tSize (KB)\tStatus\n");
    printf("-----\t---------\t------\n");
    for (int i = 0; i < n_blocks; i++)
    {
        printf("%d\t%d\t\t%s\n", i, blocks[i].size, blocks[i].is_free ? "Free" : "Allocated");
    }
    printf("\n");
}

// Best Fit Strategy
void best_fit(Block blocks[], int n_blocks, int request_size)
{
    int best_index = -1;
    for (int i = 0; i < n_blocks; i++)
    {
        if (blocks[i].is_free && blocks[i].size >= request_size)
        {
            if (best_index == -1 || blocks[i].size < blocks[best_index].size)
            {
                best_index = i;
            }
        }
    }

    if (best_index != -1)
    {
        printf("Allocated %d KB in block %d (Best Fit)\n", request_size, best_index);
        blocks[best_index].is_free = 0;
        int remaining = blocks[best_index].size - request_size;
        if (remaining > 0)
        {
            // Shift blocks to create a new free block
            for (int j = n_blocks - 1; j > best_index; j--)
            {
                blocks[j] = blocks[j - 1];
            }
            blocks[best_index].size = request_size;
            blocks[best_index + 1] = (Block){remaining, 1};
        }
        return;
    }
    printf("No block found to fit the request of %d KB (Best Fit)\n", request_size);
}

// Main Function
int main()
{
    Block blocks[MAX_BLOCKS];
    int n_blocks = 4;
    int request_size = 150;

    // Best Fit
    initialize_blocks(blocks, n_blocks); // Re-initialize for a fresh start
    printf("......................\n");
    printf("Before allocation (Best Fit):\n");
    print_blocks(blocks, n_blocks);
    best_fit(blocks, n_blocks, request_size);
    printf("......................\n");

    printf("After allocation (Best Fit):\n");
    print_blocks(blocks, n_blocks);

    return 0;
}
