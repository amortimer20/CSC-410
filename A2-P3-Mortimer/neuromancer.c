// A NEUROMANCER CYBER HEIST - help needed with synchronization
// Task: Make this a fair game where the players take turns

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PLAYERS 3
#define GAME_DURATION 10 


int currentPlayer = 0; // Index of the current player
int gameActive = 1;    // Game state
int scores[NUM_PLAYERS] = {0}; // Keep track of each player's score

// Mutex and condition
// Mutex protects access to game state
// Condition makes sure each player knows when it's their turn
pthread_mutex_t turnLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t turnCompleted = PTHREAD_COND_INITIALIZER;


void* hack(void* arg) {
    int id = *(int*)arg;

    while (gameActive) {

        // Lock the current game state
        pthread_mutex_lock(&turnLock);

        // Player waits until it is their turn, but only continues if the 
        // game is still going; Rechecked after every wake
        while (currentPlayer != id && gameActive)
        {
            pthread_cond_wait(&turnCompleted, &turnLock);
        }

        // Don't take turn if game is over
        if (!gameActive)
        {
            // Unlock mutex so players aren't stuck blocking
            pthread_mutex_unlock(&turnLock);
            break;
        }

        // Simulate hacking
        printf("Player %d is attempting to hack... -------------- Current Player (%d)\n", id + 1, currentPlayer+1);
        sleep(1);


        // Randomly determine success or failure
        int hackResult = rand() % 10 + 1;
        if (hackResult <= 6) { // 60% chance of success
            printf("Player %d succeeded in hacking!\n", id + 1);
            scores[id]++;
        } else {
            printf("Player %d failed to hack!\n", id + 1);
        }

        // Move to the next player
        currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;

        // Tell other players turn is over
        pthread_cond_broadcast(&turnCompleted);
        pthread_mutex_unlock(&turnLock);
    }
    
    return NULL;
}

int main() {
    pthread_t players[NUM_PLAYERS];
    int playerIds[NUM_PLAYERS];
    int winner = 0;

    srand(time(NULL));
    

    // Start player threads
    for (int i = 0; i < NUM_PLAYERS; i++) {
        playerIds[i] = i;
        pthread_create(&players[i], NULL, hack, &playerIds[i]);
    }

    // Let the game run for a specified duration
    sleep(GAME_DURATION);
    gameActive = 0; // End the game
    
    // Wake players waiting for a turn; Game is already over
    pthread_cond_broadcast(&turnCompleted);
    pthread_mutex_unlock(&turnLock);


    // Join player threads
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        pthread_join(players[i], NULL);
    }

    printf("--------- GAME OVER! ---------\n\n");

    int maxScore = scores[0];
    for (int i = 0; i < NUM_PLAYERS; i++){
        if(scores[i] > maxScore) {
            maxScore = scores[i];
            winner = i;
        }
    }
    printf("Player %d wins with %d points\n", winner+1, scores[winner]);

    
    return 0;
}
