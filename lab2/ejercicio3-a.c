#include <stdio.h>
#include <time.h>

int main()
{
	clock_t inicio, final;
    int iter = 1000000;


	inicio = clock();

	for (int i = 0; i < iter; i++) { 
        printf("%d\n", i); };
	for (int i = 0; i < iter; i++) { 
        printf("%d\n", i); };
	for (int i = 0; i < iter; i++) { 
        printf("%d\n", i); };

	final = clock();

	double tiempo = (double)(final - inicio)/CLOCKS_PER_SEC;
	printf("%f\n", tiempo);




    
	return 0;
}