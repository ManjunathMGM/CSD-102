#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Bin_heap
{ // Minimum Heap

    int *bin_array;        // Contain array heap tree
    unsigned int size;     // size of array
    unsigned int last_pos; // position
} Bin_heap;

// Functions Provided ---------------------------------
Bin_heap *initialize_heap(unsigned int size)
{

    Bin_heap *bh = malloc(sizeof(Bin_heap));
    bh->size = (unsigned int)pow(2, ceil(log2(size)));
    bh->bin_array = (int *)malloc(bh->size * sizeof(int));
    if (bh->bin_array == NULL)
    {
        printf("Memory not assigned\n");
        exit(0);
    }
    bh->last_pos = 0;
    for (unsigned int i = 0; i < bh->size; i++)
    {
        bh->bin_array[i] = 50000;
    }
    return bh;
}
int top_heap(Bin_heap *hp)
{
    return hp->bin_array[0];
}
void print_BFS(Bin_heap *hp)
{
    // Breadth First Traversal
    unsigned int i;
    for (i = 0; i < hp->last_pos; i++)
    {
        printf("%d ", hp->bin_array[i]);
    }
    printf("\n");
}

//---- Functions to be implemented -----------------------
void push_heap(Bin_heap *hp, int value)
{

    if (hp->last_pos == hp->size)
    {
        // Resize the array if it's full
        hp->size *= 2;
        hp->bin_array = realloc(hp->bin_array, hp->size * sizeof(int));
        if (hp->bin_array == NULL)
        {
            printf("Memory not assigned\n");
            exit(0);
        }
    }

    // Add the new value to the end of the array
    hp->bin_array[hp->last_pos] = value;

    // Perform heapify-up to maintain the heap property
    unsigned int current_pos = hp->last_pos;
    while (current_pos > 0 && hp->bin_array[current_pos] < hp->bin_array[(current_pos - 1) / 2])
    {
        // Swap with parent
        int temp = hp->bin_array[current_pos];
        hp->bin_array[current_pos] = hp->bin_array[(current_pos - 1) / 2];
        hp->bin_array[(current_pos - 1) / 2] = temp;

        // Move up the tree
        current_pos = (current_pos - 1) / 2;
    }

    // Increment the last_pos
    hp->last_pos++;
}

void pop_heap(Bin_heap *hp)
{

    if (hp->last_pos == 0)
    {
        printf("Heap is empty\n");
        return;
    }

    // Replace the root with the last element
    hp->bin_array[0] = hp->bin_array[hp->last_pos - 1];

    // Perform heapify-down to maintain the heap property
    unsigned int current_pos = 0;
    while (1)
    {
        unsigned int left_child = 2 * current_pos + 1;
        unsigned int right_child = 2 * current_pos + 2;
        unsigned int smallest = current_pos;

        if (left_child < hp->last_pos && hp->bin_array[left_child] < hp->bin_array[smallest])
        {
            smallest = left_child;
        }

        if (right_child < hp->last_pos && hp->bin_array[right_child] < hp->bin_array[smallest])
        {
            smallest = right_child;
        }

        if (smallest != current_pos)
        {
            // Swap with the smallest child
            int temp = hp->bin_array[current_pos];
            hp->bin_array[current_pos] = hp->bin_array[smallest];
            hp->bin_array[smallest] = temp;

            // Move down the tree
            current_pos = smallest;
        }
        else
        {
            break;
        }
    }

    // Decrement the last_pos
    hp->last_pos--;
}
//------------------------------------------------------------
int main()
{

    int size = 0;
    scanf("%d", &size);

    Bin_heap *bh = initialize_heap((unsigned int)size);
    int temp;
    for (unsigned int i = 0; i < size; i++)
    {
        scanf("%d", &temp);
        push_heap(bh, temp);
    }

    for (unsigned int i = 0; i < size; i++)
    {

        int top = top_heap(bh);
        pop_heap(bh);
        printf("%d ", top);
    }
    printf("\n");
    return 0;
}
