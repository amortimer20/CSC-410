#include "matrixT.h"

int main() 
{
    // declare thread id and thread data
    thread_data_t threadData[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].thread_id = i;

        if (i < NUM_THREADS - 1)
        {
            threadData[i].num_rows = N / NUM_THREADS;
        }
        else
        {
            // Give last thread remaining rows
            threadData[i].num_rows = N / NUM_THREADS + N % NUM_THREADS;
        } 
    }
    
    // Dynamically allocate memory for the matrices
    A = (int**)malloc(N * sizeof(int*));
    B = (int**)malloc(N * sizeof(int*));
    C = (int**)malloc(N * sizeof(int*));

    for (int i = 0; i < N; ++i) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
    }

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    // Initialize matrices A and B with values
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    printf("Matrices initialized successfully.\n");

    // Create threads to perform matrix multiplication
    for (int i = 0; i < NUM_THREADS; i++)
    {
        // Eventually Populate arg
        pthread_create(&threadData[i], NULL, matrixMultiplyThread, NULL);
    }
    

    // Wait for all threads to complete


    printf("Matrix multiplication complete!\n");

    // Optionally, display the resulting matrix C (Not when you are timing :) )
    displayMatrix(C, N);

    // Free dynamically allocated memory
    for (int i = 0; i < N; ++i) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}