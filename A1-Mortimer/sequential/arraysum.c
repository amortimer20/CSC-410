#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000000

long long sumArray(int arr[], int size)
{
    long long sum = 0;

    for (int i = 0; i < size; i++)
        sum += arr[i];

    return sum;
}

int main()
{
    // int arr[SIZE];
    int *arr = (int*)malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = i + 1;
    }
    
    long long totalSum = sumArray(arr, SIZE);
    printf("Total Sum: %lld\n", totalSum);

    return 0;
}