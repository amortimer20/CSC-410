#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ITERATIONS 1000000

pthread_mutex_t lock;
// long counter = 0; // shared by every thread
long sum = 0;

void *worker(void *arg)
{
    long long localSum = 0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        localSum++;
    }
    

    // for (int i = 0; i < ITERATIONS; i++)
    // {
    //     pthread_mutex_lock(&lock);
    //     counter++;
    //     pthread_mutex_unlock(&lock);
    // }

    long long *partialSumSlot = (long long *)arg;
    *partialSumSlot = localSum;

    return NULL;
}

int main(void)
{
    pthread_t tids[NUM_THREADS];
    long long partialSums[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&tids[i], NULL, worker, &partialSums[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(tids[i], NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        sum += partialSums[i];
    }
    


    printf("counter: %ld (expected %d)\n", sum, NUM_THREADS * ITERATIONS);        
}