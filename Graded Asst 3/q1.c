#include <math.h>
#include <stdio.h>

// A utility function to print an array of size n
// DO NOT EDIT
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = low;
        int pivot = arr[high];
        for (int i = low; i < high; i++)
        {
            if (arr[i] <= pivot)
            {
                swap(&arr[i], &arr[pivotIndex]);
                pivotIndex++;
            }
        }
        swap(&arr[pivotIndex], &arr[high]);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
    return;
}

// DO NOT EDIT
int main()
{

    int size = 0;
    scanf("%d", &size);

    int arr[size];
    int temp;
    for (unsigned int i = 0; i < size; i++)
    {
        scanf("%d", &temp);
        arr[i] = temp;
    }
    quickSort(arr, 0, size - 1);
    printArray(arr, size);
    return 0;
}
