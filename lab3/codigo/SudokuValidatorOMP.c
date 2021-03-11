#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ROW 9
#define COLUMN 9
#define true 1

char sudoku[ROW][COLUMN];
int valid_columns, valid_rows;

int ProbarNumerosColumna(int board[9][9]) {
    int result = 1;
    omp_set_num_threads(9);
    omp_set_nested(1==1);
    #pragma omp parallel for schedule(dynamic)
    for(int number=1; number<=9;number++) {
        int times=0;
        for(int  i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[j][i] == number) {
                  times++;  
                }
            }
        }
        if(times!=1){
            result = 0;
        }
    }
    return result;
}

int ComprobarFilas()
{
    omp_set_nested(true);
    omp_set_num_threads(9);

    int grid[9];
    int valid = 0;
    #pragma omp parallel for private(grid) schedule(dynamic)
    for (int i = 0; i < ROW; i++)
    {
        char valid_nums[] = "123456789";
        char *s;
        for (s = &valid_nums[0]; *s != '\0'; s++)
        {
            int found = 0;
            int j = 0;
            while (found == 0 && j < COLUMN)
            {
                if (sudoku[i][j] == *s)
                    found = 1;
                j++;
            }
            if (found == 0)
                valid = -1;
        }
    }
    return valid;
}
int ProbarNumeroFila(int board[9][9]){
    int times;
    int result = 1;
    omp_set_nested(1==1);
    omp_set_num_threads(9);
    #pragma omp parallel for 
    for(int number=1; number<=9;number++) {
        for(int  i=0;i<9;i++){
            times=0;
            for(int j=0;j<9;j++){
                if(board[i][j] == number) {
                  times++;  
                }
            }
            if(times!=1){
                result = 0;
            }
        }
    }
    return result;
}
int ComprobarArgumentoFila(char temp[ROW][COLUMN])
{
    omp_set_nested(true);
    omp_set_num_threads(9);

    int grid[9];
    int valid = 0;
    #pragma omp parallel for private(grid) schedule(dynamic)
    for (int i = 0; i < ROW; i++)
    {
        char valid_nums[] = "123456789";
        char *s;
        for (s = &valid_nums[0]; *s != '\0'; s++)
        {
            int found = 0;
            int j = 0;
            while (found == 0 && j < COLUMN)
            {
                if (temp[i][j] == *s)
                    found = 1;
                j++;
            }
            if (found == 0)
                valid = -1;
        }
    }
    return valid;
}
int ProbarNumeroLista(int row, int column, int board[9][9]){
    int result = 1;
    omp_set_num_threads(9);
    omp_set_nested(1==1);
    #pragma omp parallel for schedule(dynamic)
    for(int number=1; number<=9;number++) {
        int times=0;
        for(int  i=row;i<row+3;i++){
            for(int j=column;j<column+3;j++){
                if(board[j][i] == number) {
                  times++;  
                }
            }
        }
        if(times!=1){
            result = 0;
        }
    }
    return result;
}
void *verificacion_columna()
{
    printf("Columna id: %d\n", syscall(SYS_gettid));
    valid_columns = verificarcolumna();
    pthread_exit(0);
}
void *verificacionfila()
{
    printf("Fila id: %d\n", syscall(SYS_gettid));
    valid_rows = verificarfila();
    pthread_exit(0);
}
int main(int argc, char *argv[])
{
    omp_set_num_threads(1);

    if (argc < 2)
    {
        printf("No");
        return 1;
    }
    int input;
    if ((input = open(argv[1], O_RDONLY)) < 0)
    {
        perror("Error");
        return 1;
    }
        if(fid == 0){ 
        printf("thread: %d\n", pid); 
        execlp("ps", "ps", "-p", strPid, "-lLF", NULL);
    }else {
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, checkNumbersClmn, *grid); //this time *grid is no useful
        void *retval;
        pthread_join(tid, &retval);
        if(ProbarNumeroFila(grid)==1){
            printf("resuelto\n");
        }
        wait(NULL);
    }
    if(fork() == 0) {
        printf("Antes:\n"); 
        execlp("ps", "ps", "-p", strPid, "-lLF", NULL);
    } else {
        wait(NULL);
    }
    munmap(f, size);
    return 0;
}