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
    unsigned int current_pos = hp->last_pos;
    unsigned int parent_pos = (current_pos - 1) / 2;
    if (hp->last_pos == hp->size)
    {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    hp->bin_array[hp->last_pos] = value;

    while (current_pos > 0 && hp->bin_array[current_pos] < hp->bin_array[parent_pos])
    {
        int temp = hp->bin_array[current_pos];
        hp->bin_array[current_pos] = hp->bin_array[parent_pos];
        hp->bin_array[parent_pos] = temp;

        current_pos = parent_pos;
        parent_pos = (current_pos - 1) / 2;
    }

    hp->last_pos++;
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

    print_BFS(bh);

    return 0;
}
