#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int READ_END = 0;
const int WRITE_END = 1;

int main(){
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "123";
	char *buffer;
	buffer = malloc(strlen(some_data) + 1);

	if(pipe(file_pipes) == 0){
		data_processed = write(file_pipes[WRITE_END], some_data, strlen(some_data));
		printf("Wrote %d bytes\n", data_processed);
		data_processed = read(file_pipes[READ_END], buffer, strlen(some_data));
		printf("Read %d bytes: %s\n", data_processed, buffer);
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	free(buffer);
	exit(EXIT_FAILURE);
}


//when you reverse the order of the write and read calls, nothing happens because
//since the pipe is reading from an empty buffer, it blocks the other end of the pipe
//until it reads data
//however, since the pipe has not wrote data yet, this blocking lasts forever
