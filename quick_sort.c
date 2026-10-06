#include <stdio.h>
#include <string.h>

struct Package {
    char id[10];
    int weight;
    int position;
};

long long comparisons = 0;

void swap(struct Package *a, struct Package *b)
{
    struct Package temp = *a;
    *a = *b;
    *b = temp;
}

void printPackages(struct Package a[], int low, int high)
{
    int i;

    for (i = low; i <= high; i++)
        printf("%s(%d) ", a[i].id, a[i].weight);

    printf("\n");
}

int partition(struct Package a[], int low, int high)
{
    int pivot = a[high].weight;
    int i = low - 1;
    int j;

    printf("\nPivot = %d\n", pivot);

    for (j = low; j < high; j++)
    {
        comparisons++;

        if (a[j].weight <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    printf("After partition: ");
    printPackages(a, low, high);

    return i + 1;
}

void quickSort(struct Package a[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex;

        pivotIndex = partition(a, low, high);

        quickSort(a, low, pivotIndex - 1);
        quickSort(a, pivotIndex + 1, high);
    }
}

int main()
{
    struct Package packages[] = {
        {"P1", 20, 1},
        {"P2", 15, 2},
        {"P3", 20, 3},
        {"P4", 10, 4},
        {"P5", 15, 5},
        {"P6", 20, 6},
        {"P7", 25, 7},
        {"P8", 10, 8}
    };

    int n = 8;
    int i;

    printf("===== QUICK SORT =====\n");

    printf("\nOriginal packages:\n");
    printPackages(packages, 0, n - 1);

    quickSort(packages, 0, n - 1);

    printf("\nFinal sorted packages:\n");

    for (i = 0; i < n; i++)
        printf("%s -> Weight = %d\n",
               packages[i].id,
               packages[i].weight);

    printf("\nNumber of comparisons = %lld\n", comparisons);

    printf("\nNote:\n");
    printf("Ordinary Quick Sort is NOT guaranteed to be stable.\n");
    printf("Therefore, equal-weight packages may not retain their original order.\n");

    return 0;
}
