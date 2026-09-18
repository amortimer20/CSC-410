// convert sequential sums to parallel

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESSES 4 

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int *arr = malloc(N * sizeof(int));
    if (!arr) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    // complete this
    long long totalSum = 0;
    int pipes[NUM_PROCESSES][2];

    // Work size = Number Length / Number of processes
    // Add leftover to last child process
    int workSize = N / NUM_PROCESSES;
    int workLeftoverSize = N % NUM_PROCESSES;

    // Open pipes
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        pipe(pipes[i]);
    }

    int startIndex = 0;
    int endIndex = startIndex + workSize;

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        if (i == 3)
        {
            endIndex += workLeftoverSize;
        }

        pid_t p = fork();

        if (p > 0)
        {
            close(pipes[i][1]); // Close parent write pipe
        }
        if (p == 0)
        {
            close(pipes[i][0]); // Close child read pipe

            // Calculate sum for current section
            long long sum = 0;

            for (int j = startIndex; j < endIndex; j++)
            {
                sum += arr[j];
            }
            
            write(pipes[i][1], &sum, sizeof(sum));
            close(pipes[i][1]);
            return 0;
        }

        // Move to next unit of work
        startIndex += workSize;
        endIndex += workSize;
    }

    // Accumulate sum from all child processes
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        wait(NULL);

        long long returnedSum;
        read(pipes[i][0], &returnedSum, sizeof(returnedSum));
        close(pipes[i][0]);
        totalSum += returnedSum;
    }
    
    printf("Total sum = %lld\n", totalSum);
    return 0;
}
