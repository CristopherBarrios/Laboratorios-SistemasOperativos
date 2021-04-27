// Cristopher Barrios 18207
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>


#define THREADS 5

pthread_mutex_t mutex;
unsigned available_resources;

void delay(int number_of_seconds) 
{ 
    // conversor ms
    int milli_seconds = 1000 * number_of_seconds; 
    // inicio tiempo 
    clock_t start_time = clock();   
    // ciclo para el tiempo 
    while (clock() < start_time + milli_seconds); 
}; 

//disminuye
int decrease_count(int count){
	if (available_resources < count) {
		return -1;
	}
	else{
		printf("\n");
		pthread_mutex_lock(&mutex);
		printf("block\n");
		printf("si hay disponibles %d \n", count);
		available_resources = available_resources - count;

		pthread_mutex_unlock(&mutex);
		printf("Desbloqueando \n");
		return 0;
	}
}

//aumenta las variables
int increase_count(int count){
	pthread_mutex_lock(&mutex);
	printf("block\n");

	printf("regresando cantidad %d \n", count);
	available_resources = available_resources + count;

	pthread_mutex_unlock(&mutex);
	printf("Desbloqueando \n");
	return 0;
}

void *resource_manager(void *custom_logger)
{
    // recurso 16
    int resources_taken = 16;
    int tid = gettid();

    fprintf(((struct logger *)custom_logger)->info, "Iniciando thread %d\n", tid);

    for (int i = 0; i < ITER_COUNT; i++)
    {
        fprintf(((struct logger *)custom_logger)->info, "Iniciando iteracion %d\n", i + 1);
        fprintf(((struct logger *)custom_logger)->info, "Se consumiran %d recursos\n", resources_taken);

        // bloqueando
        pthread_mutex_lock(&mutex);

        shared_resources++;
        fprintf(((struct logger *)custom_logger)->info, "%d -- (!) - Recurso tomado\n", tid);
        fprintf(((struct logger *)custom_logger)->info, "%d -- (.) - usando recurso\n", tid);

        // disminuyendo e incrementando
        fprintf(((struct logger *)custom_logger)->info, "-- ()- recurso devuelto\n");
        decrease_count(resources_taken, (void *)((struct logger *)custom_logger));
        increase_count(resources_taken, (void *)((struct logger *)custom_logger));

        // desbloqueando mutex
        pthread_mutex_unlock(&mutex);
        fprintf(((struct logger *)custom_logger)->info, " -- :) - recurso usado\n");
    }
    pthread_exit(0);
}

// el famosisimo main
int main() {
	FILE *fptr;
	fptr = fopen("monLog.txt", "w");

	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fprintf(fptr, "Iniciando iteracion\n");
	int j;
	pthread_t *thread;

	available_resources = 20;

	fprintf(fptr, "Creando %d threads\n", THREADS);
	for (j = 0; j < THREADS; j++) {
		pthread_create(&thread[j], NULL, threads_to_do, NULL);
	}

	fprintf(fptr, "Esperando threads \n");
	for (j = 0; j < THREADS; j++) {
		pthread_join(thread[j], NULL);
	}

	fprintf(fptr, "Fin del programa \n");
	fclose(fptr);
	return 0;
}