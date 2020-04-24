#include <stdio.h>
#include <unistd.h>

int gval = 10;
int main(int argc, char *argv[])
{
    pid_t pid;
    int lval = 20; 
    gval ++;        // gval = 11
    lval +=5;       // lval = 25

    pid = fork(); 
    if(pid == 0)    // if Child Process
        gval += 2, lval += 2;            // gval = 13 lval = 27
    else            // if Parent Process
        gval -= 2, lval -= 2;            // gval = 9 lval = 23

    if(pid == 0)
        printf("Child Proc: [%d, %d] \n", gval, lval);
    else 
        printf("Parent Proc: [%d, %d] \n", gval, lval);
    for(;;)
    {
        
    }
    return 0;
}