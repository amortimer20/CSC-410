#include "sorts.h"

// Merge Sort 
static void merge(int arr[], int left, int mid, int right) 
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftTempArr[leftSize];
    int rightTempArr[rightSize];

    for (int i = 0; i < leftSize; i++)
    {
        leftTempArr[i] = arr[left + i];
    }

    for (int i = 0; i < rightSize; i++)
    {
        rightTempArr[i] = arr[mid + i + 1];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < leftSize && j < rightSize)
    {
        if (leftTempArr[i] <= rightTempArr[j])
        {
            arr[k] = leftTempArr[i];
            i++;
        }
        else
        {
            arr[k] = rightTempArr[j];
            j++;
        }

        k++;
    }

    while (i < leftSize)
    {
        arr[k] = leftTempArr[i];
        i++;
        k++;
    }

    while (j < rightSize)
    {
        arr[k] = rightTempArr[j];
        j++;
        k++;
    }

}

void mergeSort(int arr[], int left, int right) 
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Bubble Sort
void bubbleSort(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
}

void printArray(int arr[], int n) 
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}