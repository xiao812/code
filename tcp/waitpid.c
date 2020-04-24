#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status; 
    pid_t pid = fork();

    if(pid == 0)
    {
        sleep(15); 
        puts("End child");
    }
    else 
    {
        sleep(5); 
        puts("End parent");
    }

    return 0;
}