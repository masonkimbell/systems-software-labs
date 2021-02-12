#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define FIFO "/tmp/task4_fifo"

const int READ_END = 0;
const int WRITE_END = 1;

int main(){
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "123";
	char *buffer;
	buffer = malloc(strlen(some_data) + 1);

	int fd = open(FIFO, O_RDWR);
	data_processed = write(fd, some_data, strlen(some_data));
	printf("Wrote %d bytes\n", data_processed);
	data_processed = read(fd, buffer, strlen(some_data));
	printf("Read %d bytes: %s\n", data_processed, buffer);
	free(buffer);
	exit(EXIT_SUCCESS);
}

//command used: mkfifo -m 666 /tmp/task4_fifo
