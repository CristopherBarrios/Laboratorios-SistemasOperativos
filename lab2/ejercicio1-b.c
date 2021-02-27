#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i=0;
    for(i; i<4; i++){
    fork();
    }
    printf("cuantos\n");

    return(0);
}