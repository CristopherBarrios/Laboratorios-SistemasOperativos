#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid1;
    pid1 = fork();

    if(pid1 == 0)
    {
        for (int i = 0; i < 4000000; i++){printf("%d\n", i);} 
    }
    else
    {
        for(;;);
    }




    return 0;
}