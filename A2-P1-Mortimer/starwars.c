#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Starting shield power level
int shield_power = 50;  

int main() {
    pid_t pid;

    printf("Millennium Falcon: Initial shield power level: %d%%\n\n", shield_power);

    // Create 4 child processes - 4 different characters adjusting shield power

            // Luke increases the shield power by 25
            pid = fork();

            if (pid == 0)
            {
                printf("Luke: Adjusting shields...\n");
                shield_power += 25;
                printf("Luke: Shield power level now at %d%%\n", shield_power);
                return 0;
            }

            // Han increases the shield power by 20
            pid = fork();

            if (pid == 0)
            {
                printf("Han: Adjusting shields...\n");
                shield_power += 20;
                printf("Han: Shield power level now at %d%%\n", shield_power);
                return 0;
            }
            // Chewbacca increases the shield power by 30
            pid = fork();

            if (pid == 0)
            {
                printf("Chewbacca: Adjusting shields...\n");
                shield_power += 30;
                printf("Chewbacca: Shield power level now at %d%%\n", shield_power);
                return 0;
            }
            // Leia increases the shield power by 15
            pid = fork();

            if (pid == 0)
            {
                printf("Leia: Adjusting shields...\n");
                shield_power += 15;
                printf("Leia: Shield power level now at %d%%\n", shield_power);
                return 0;
            }
               

    // Check if process creation failed
    if (pid == -1)
    {
        printf("Fork failed.");
        return -1;
    }
    
    // Make parent process wait for all child processes to complete 
    for (int i = 0; i < 4; i++)
    {
        wait(NULL);
    }
    


    // Parent process reports final state
    printf("\nFinal shield power level on the Millennium Falcon: %d%%\n", shield_power);
    printf("\nMay the forks be with you!\n");
    return 0;
}
