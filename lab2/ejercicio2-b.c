#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2, pid3;
    clock_t inicio, final;
    int iter = 1000000;

    inicio = clock();
    pid1 = fork(); 
    if(pid1 == 0) {
        pid2 = fork();
        if(pid2 == 0){    
            pid3 = fork();
            if(pid3 == 0) {
                for (int i = 0; i < iter; i++);
            }else{
                for (int i = 0; i < iter; i++);
                wait(NULL);
            }
        }else {
            for (int i = 0; i < iter; i++);
            wait(NULL);
        }}
    else {
        wait(NULL);
        final = clock();
        printf("Tiempo es %f seg\n", (double) final - inicio);
    }




    
    return 0;
}