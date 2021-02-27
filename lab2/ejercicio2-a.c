#include <stdio.h>
#include <time.h>

int main()
{
    clock_t inicio;
    clock_t apocalipsis;
    inicio = clock();
    
    for (int i = 0; i < 1000000; i++){

    }
    for (int i = 0; i < 1000000; i++){

    }
    for (int i = 0; i < 1000000; i++){

    }
    apocalipsis = clock();
    double reloj = (double) apocalipsis - inicio;

    printf("El tiempo es %f seg\n", reloj);

    return 0;
}