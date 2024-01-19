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

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* Function to sort an array using merge sort*/
/* l is for left index and r is right index of the
sub-array of arr to be sorted */

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves

        mergeSort(arr, l, m);

        mergeSort(arr, m + 1, r);

        // Merge the sorted halves

        merge(arr, l, m, r);
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
    mergeSort(arr, 0, size - 1);
    printArray(arr, size);
    return 0;
}
