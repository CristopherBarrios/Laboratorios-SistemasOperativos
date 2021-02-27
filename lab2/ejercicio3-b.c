#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	clock_t inicio, final;
	pid_t pid1, pid2, pid3;
    int iter = 1000000;
    int i;

	inicio = clock();
	pid1 = fork();

	if (pid1 == 0){
		pid2 = fork();
		if (pid2 == 0){
			pid3 = fork();
			if (pid3 == 0){
				for ( i = 0; i < iter; i++) { 
                    printf("%d\n", i); };
			}
			else{
				for ( i = 0; i < iter; i++) { 
                    printf("%d\n", i); };
				wait(NULL);
			}
		}
		else{
			for ( i = 0; i < iter; i++) { 
                    printf("%d\n", i); };
			wait(NULL);
		}
	}
	else{
		wait(NULL);
        
		final = clock();
		double tiempo = (double)(final - inicio) / CLOCKS_PER_SEC;
		printf("%f\n", tiempo);
	}
	return 0;
}