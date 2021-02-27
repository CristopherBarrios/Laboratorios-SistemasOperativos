#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>


#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main (int argc, char**argv) {
	const int SIZE = 4096;
	
    pid_t pid;
	int value = 0;
	int n, named_fd, fd[2];
    const int SIZE = 4096;
    const char* NAME = "/OS"; 
	char * myfifo = "/tmp/myfifo";
	int shm_fd;
	char *ptr;

    if(argc != 3) {
        fprintf(stderr, "Invalid params\n");
        return 1;
    }

	n = atoi(argv[1]);
	char x[sizeof(argv[2])];

	strcpy(x, argv[2]);
    	int end = -1;

	
	printf("Yo soy %c\n", x[0]);
	mkfifo(myfifo, 0666);

    int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED;

	shm_fd = shm_open(NAME, O_RDWR, 0);

	if (shm_fd == -1){
		shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
		printf("%c: Create a new shared memory object %d\n", x[0], shm_fd);
		ftruncate(shm_fd, SIZE);
		named_fd = open(myfifo, O_WRONLY);
		write(named_fd, &fin, sizeof(end));
		close(named_fd);
		printf("%c: Initialized shared memory object\n", x[0]);
	}
	
	else 
	{
		printf("%c: Share mem obj already created\n", x[0]);
		named_fd = open(myfifo, O_RDONLY);
		read(named_fd, &value, sizeof(value));
		close(named_fd);
		printf("%c: Received shm fd: %d\n", x[0], value);
		ftruncate(shm_fd, SIZE);
	}
	ptr = mmap(0, SIZE, protection, visibility, shm_fd, 0);
	printf("%c: ptr created with value %p\n", x[0], ptr);
	
	char write_msg[BUFFER_SIZE];
	char read_msg[BUFFER_SIZE];
	sprintf(write_msg, "%s", x);
	int fd[2];
	pipe(fd);

    if(pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }
 	pid = fork();
	if (pid > 0 ) {	
	 	for (int i=0; i<SIZE; i++)
	 	{
	 		if (i%n == 0){
				close(fd[READ_END]);
	 			write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
			 	close(fd[WRITE_END]);}}
		wait(NULL);
	 	printf("%c: Shared memory has %s\n", x[0], (char *)ptr);
	 	if (value == 0) 
	 	{
			shm_unlink(NAME);	
	 	}
	}else {
		
		if (value < 0) 
		{
	 		ptr += 26;
	 	}	
		int s = 0;
		while(s < SIZE/n +1)
		{
			close(fd[WRITE_END]);
		 	read(fd[READ_END], read_msg, BUFFER_SIZE);
			close(fd[READ_END]);
			
				sprintf(ptr, "%s", (char *)read_msg);
			 	ptr += strlen(read_msg);
			s = s+ 1;
		}
	}
    shm_unlink(NAME);
    close(named_fd);
	munmap(ptr, SIZE);
	shm_unlink(NAME);
	
	return 0;	
}