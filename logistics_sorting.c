#include <stdio.h>
#include <string.h>

#define N 8

/* Structure to store package information */
struct Package
{
    char id[10];
    int weight;
    int original_position;
};

/* Counters for comparisons */
long long mergeComparisons = 0;
long long quickComparisons = 0;

/* ---------------------------------------------------------
   Utility Functions
   --------------------------------------------------------- */

void printPackages(struct Package a[], int n)
{
    int i;

    printf("--------------------------------------------------\n");
    printf("Package ID\tWeight\tOriginal Position\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%s\t\t%d\t%d\n",
               a[i].id,
               a[i].weight,
               a[i].original_position);
    }

    printf("--------------------------------------------------\n");
}

/* ---------------------------------------------------------
   MERGE SORT
   --------------------------------------------------------- */

void merge(struct Package a[], int low, int mid, int high)
{
    struct Package temp[N];

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        mergeComparisons++;

        /*
           <= is important here.
           When weights are equal, the element from the
           left subarray is selected first.

           This makes Merge Sort STABLE.
        */
        if (a[i].weight <= a[j].weight)
        {
            temp[k] = a[i];
            i++;
        }
        else
        {
            temp[k] = a[j];
            j++;
        }

        k++;
    }

    /* Copy remaining elements from left half */
    while (i <= mid)
    {
        temp[k] = a[i];
        i++;
        k++;
    }

    /* Copy remaining elements from right half */
    while (j <= high)
    {
        temp[k] = a[j];
        j++;
        k++;
    }

    /* Copy sorted elements back */
    for (i = low; i <= high; i++)
    {
        a[i] = temp[i];
    }
}

void mergeSort(struct Package a[], int low, int high)
{
    int mid;

    if (low < high)
    {
        mid = (low + high) / 2;

        /* Divide */
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        /* Conquer */
        merge(a, low, mid, high);

        printf("\nMerge step: positions %d to %d\n",
               low + 1, high + 1);

        printPackages(&a[low], high - low + 1);
    }
}

/* ---------------------------------------------------------
   QUICK SORT
   --------------------------------------------------------- */

int partition(struct Package a[], int low, int high)
{
    int pivot = a[high].weight;
    int i = low - 1;
    int j;

    printf("\nQuick Sort Partition\n");
    printf("Low = %d, High = %d, Pivot = %d\n",
           low + 1, high + 1, pivot);

    for (j = low; j < high; j++)
    {
        quickComparisons++;

        if (a[j].weight <= pivot)
        {
            struct Package temp;

            i++;

            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    /* Place pivot in correct position */
    {
        struct Package temp;

        temp = a[i + 1];
        a[i + 1] = a[high];
        a[high] = temp;
    }

    printf("After partition:\n");
    printPackages(&a[low], high - low + 1);

    return i + 1;
}

void quickSort(struct Package a[], int low, int high)
{
    int pivotIndex;

    if (low < high)
    {
        pivotIndex = partition(a, low, high);

        quickSort(a, low, pivotIndex - 1);
        quickSort(a, pivotIndex + 1, high);
    }
}

/* ---------------------------------------------------------
   STABILITY CHECK
   --------------------------------------------------------- */

void checkStability(struct Package a[], int n)
{
    int i;

    printf("\nSTABILITY CHECK\n");
    printf("==============================\n");

    for (i = 1; i < n; i++)
    {
        if (a[i].weight == a[i - 1].weight)
        {
            if (a[i].original_position <
                a[i - 1].original_position)
            {
                printf("Result: NOT STABLE\n");
                return;
            }
        }
    }

    printf("Result: STABLE\n");
}

/* ---------------------------------------------------------
   MAIN FUNCTION
   --------------------------------------------------------- */

int main()
{
    struct Package original[N] =
    {
        {"P1", 20, 1},
        {"P2", 15, 2},
        {"P3", 20, 3},
        {"P4", 10, 4},
        {"P5", 15, 5},
        {"P6", 20, 6},
        {"P7", 25, 7},
        {"P8", 10, 8}
    };

    struct Package mergeArray[N];
    struct Package quickArray[N];

    int i;

    /* Copy original data */
    for (i = 0; i < N; i++)
    {
        mergeArray[i] = original[i];
        quickArray[i] = original[i];
    }

    /* -----------------------------------------------------
       ORIGINAL DATA
       ----------------------------------------------------- */

    printf("\n===============================================\n");
    printf("     LOGISTICS PACKAGE SORTING SYSTEM\n");
    printf("===============================================\n");

    printf("\nORIGINAL PACKAGE DATA\n");
    printPackages(original, N);

    /* -----------------------------------------------------
       MERGE SORT
       ----------------------------------------------------- */

    printf("\n\n===============================================\n");
    printf("                 MERGE SORT\n");
    printf("===============================================\n");

    mergeSort(mergeArray, 0, N - 1);

    printf("\nFINAL MERGE SORT RESULT\n");
    printPackages(mergeArray, N);

    printf("\nMerge Sort Comparisons = %lld\n",
           mergeComparisons);

    checkStability(mergeArray, N);

    /* -----------------------------------------------------
       QUICK SORT
       ----------------------------------------------------- */

    printf("\n\n===============================================\n");
    printf("                 QUICK SORT\n");
    printf("===============================================\n");

    quickSort(quickArray, 0, N - 1);

    printf("\nFINAL QUICK SORT RESULT\n");
    printPackages(quickArray, N);

    printf("\nQuick Sort Comparisons = %lld\n",
           quickComparisons);

    checkStability(quickArray, N);

    /* -----------------------------------------------------
       COMPARISON
       ----------------------------------------------------- */

    printf("\n\n===============================================\n");
    printf("             ALGORITHM COMPARISON\n");
    printf("===============================================\n");

    printf("\nMerge Sort:\n");
    printf("Time Complexity - Best    : O(n log n)\n");
    printf("Time Complexity - Average : O(n log n)\n");
    printf("Time Complexity - Worst   : O(n log n)\n");
    printf("Space Complexity          : O(n)\n");
    printf("Stable                    : YES\n");

    printf("\nQuick Sort:\n");
    printf("Time Complexity - Best    : O(n log n)\n");
    printf("Time Complexity - Average : O(n log n)\n");
    printf("Time Complexity - Worst   : O(n^2)\n");
    printf("Space Complexity          : O(log n) average\n");
    printf("Stable                    : NO (ordinary Quick Sort)\n");

    printf("\n===============================================\n");
    printf("                 CONCLUSION\n");
    printf("===============================================\n");

    printf("\nWhen maintaining the original order of packages\n");
    printf("with equal weights is important, Merge Sort is\n");
    printf("more suitable because it can be implemented as\n");
    printf("a stable sorting algorithm.\n");

    printf("\nFor this data, equal-weight packages should appear as:\n");

    printf("10 kg : P4 -> P8\n");
    printf("15 kg : P2 -> P5\n");
    printf("20 kg : P1 -> P3 -> P6\n");

    printf("\nTherefore, stable Merge Sort preserves the required\n");
    printf("relative order of equal-weight packages.\n");

    return 0;
}
