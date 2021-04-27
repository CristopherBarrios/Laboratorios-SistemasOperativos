// Cristopher Barrios
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define THREADS 5
#define REP 4

int counter = 5000;
sem_t mut;

void delay(int number_of_seconds) 
{ 
    int milli_seconds = 1000 * number_of_seconds; 
    clock_t start_time = clock();   
    while (clock() < start_time + milli_seconds); 
}; 

void* threads_to_do(void) {
	int i;

	pid_t id;
	id = syscall(SYS_gettid);

	printf("Id actual: %d - Semaforo creado \n", id);

	for (i = 0; i < REP; i++) {
		sem_wait(&mut);

		printf("Repeticion numero %d \n", i + 1);

		counter = counter - 1;

		printf("Id actual: %d -- (!) - recurso tomado \n", id);

		int time = (rand() % 2) + 1;
		sleep(time);

		printf("Id actual: %d -- :) - recurso usado \n", id);

		counter = counter + 1;

		printf("Id actual: %d -- () - recurso devuelto \n", id);

		sem_post(&mut);
	}
}

//El famosisimo main
int main(void)
{

    FILE *file;
    file = fopen("semLog.txt", "wt");
    struct logger *log_file = (struct logger *)malloc(sizeof(struct logger));
    log_file->info = file;

    printf("generando...\n");
    fprintf(file, "Iniciando iteracion\n");
    fprintf(file, "Creando threads\n");

    pthread_t thread[THREAD_COUNT];
    sem_init(&sem, 0, 1);

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_create(&thread[i], NULL, *resource_manager, (void *)log_file);

    for (int j = 0; j < THREAD_COUNT; j++)
        pthread_join(thread[j], NULL);

    fclose(file);
    return 0;
}
