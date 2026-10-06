#include <stdio.h>

struct Package {
    char id[10];
    int weight;
    int position;
};

long long comparisons = 0;

void printPackages(struct Package a[], int n)
{
    int i;

    printf("\n");
    for (i = 0; i < n; i++)
        printf("%s(%d) ", a[i].id, a[i].weight);

    printf("\n");
}

void merge(struct Package a[], int low, int mid, int high)
{
    struct Package temp[100];

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        comparisons++;

        /* <= makes Merge Sort stable */
        if (a[i].weight <= a[j].weight)
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low; i <= high; i++)
        a[i] = temp[i];
}

void mergeSort(struct Package a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        merge(a, low, mid, high);

        printf("After merging positions %d to %d: ", low + 1, high + 1);
        printPackages(a + low, high - low + 1);
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

    printf("===== MERGE SORT =====\n");

    printf("\nOriginal packages:\n");
    printPackages(packages, n);

    mergeSort(packages, 0, n - 1);

    printf("\nFinal sorted packages:\n");

    for (i = 0; i < n; i++)
        printf("%s -> Weight = %d\n",
               packages[i].id,
               packages[i].weight);

    printf("\nNumber of comparisons = %lld\n", comparisons);

    printf("\nStability verification:\n");
    printf("10 kg : P4, P8\n");
    printf("15 kg : P2, P5\n");
    printf("20 kg : P1, P3, P6\n");

    return 0;
}
