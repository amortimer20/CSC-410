#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid > 0)
    {
        printf("I'm the parent, my child's pid is %d\n", pid);
    }
    else if (pid == 0)
    {
        printf("I'm the child, my pid is %d\n", pid);
        return 0;
    }
    else
    {
        printf("fork failed\n");
        return -1;
    }

    wait(NULL);
    return 0;
}