#include <stdio.h>
#include <stdlib.h> // For malloc() and free()

#define N 4 // Adjust this to test larger matrix sizes

void displayMatrix(int** matrix, int n) 
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrixMultiply(int** A, int** B, int** C, int n) 
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                // printf("A: ([%d,%d])\tB: ([%d,%d])\tC: ([%d,%d])\n", i, k, k, j, i, j);
                C[i][j] += A[i][k] * B[k][j];
            }
            
        }
        
    }
    
}


/*

[a0, a1, a2]    [b0, b1, b2]    [a0xb0+a1xb3+a2*b6, c1, c2]
[a3, a4, a5]    [b3, b4, b5]    [c3, c4, c5]
[a6, a7, a8]    [b6, b7, b8]    [c6, c7, c8]

*/