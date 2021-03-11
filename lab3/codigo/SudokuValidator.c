#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <pthread.h>
#include <sys/syscall.h>


int grid[9][9];

int ProbarNumerosColumna(int board[9][9]) {
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
            return 0;
        }
    }
    return 1;
}
int ProbarNumeroFila(char temp[ROW][COLUMN])
{
    omp_set_nested(true);
    omp_set_num_threads(9);

    int grid[9];
    int valid = 0;

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
            return 0;
        }
    }
    return 1;
}
int ComprobarMatrix()
{
    omp_set_nested(true);
    omp_set_num_threads(3);

    char temp_sudoku[ROW][COLUMN];
    int row = 0, column = 0;

    int grid[9];
    for (int x = 0; x < 3; x++)
    {
        #pragma omp parallel for
        for (int y = 0; y < 3; y++)
        {

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    temp_sudoku[row][column] = sudoku[i + (x * 3)][j + (y * 3)];
                    column++;
                }
            }
            column = 0;
            row++;
        }
    }
    return ProbarNumeroLista(temp_sudoku);
}

void *verificacion_columna()
{
    printf("Columna ID: %d\n", syscall(SYS_gettid));
    valid_columns = verificarcolumna();
    pthread_exit(0);
}

void *verificacion_fila()
{
    printf("Fila ID: %d\n", syscall(SYS_gettid));
    valid_rows = verificarfila();
    pthread_exit(0);
}

int main(int argc, char** argv) {
    unsigned char *f;
    pid_t fid;
    int fd = open(argv[1], O_RDONLY);
    pthread_attr_t attr;
    struct stat s;
    pthread_t tid;
    int size, index=0;
    int status = fstat(fd, &s);
    size = s.st_size;
    f = (char *) mmap(0,size,PROT_READ, MAP_PRIVATE, fd, 0);
    for(int i=0; i<9; i++){
        for(int j=1; j<10; j++){
            grid[i][j-1] = f[index]-'0'; 
            index++;
        }
    }
    for(int i=0;i<=8;i=i+3){
        if(verificacionfila(i, i, grid) == 0){
            return 0;
        }
    }
    int pid = getpid();  
    fid = fork();
    if(fid == 0){ 
        char strPid[20]; 
        sprintf(strPid, "%d", pid);
        printf("thread: %d\n", pid); 
        execlp("ps", "ps", "-p", strPid, "-lLF", NULL);
    } else {
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, checkNumbersClmn, *grid); 
        void *retval;
        pthread_join(tid, &retval);
        if(verificacionfila(grid)==1){
            printf("resuelto\n");
        }
        wait(NULL);

    }if(fork() == 0) {
        printf("threads:"); 
        char strPid[20]; 
        sprintf(strPid, "%d", pid);
        execlp("ps", "ps", "-p", strPid, "-lLF", NULL);
    } else {
        wait(NULL);
    }
    munmap(f, size);
    return 0;
}
