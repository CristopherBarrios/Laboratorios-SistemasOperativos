#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include<stdbool.h>


int main()
{
    pid_t pid1;
    pid1 = fork();

    if(pid1 == 0){ printf("hola \n");}

    else{
        for(;;);
    }




    
    return 0;
}