#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	int data_processed;
	char buffer[BUFSIZ + 1];
	int file_descriptor;
	
	memset(buffer, '\0', sizeof(buffer));
	sscanf(argv[1], "%d", &file_descriptor);
	data_processed = read(file_descriptor, buffer, BUFSIZ);

	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);

	int file_descriptor2;
	sscanf(argv[2], "%d", &file_descriptor2);
	char msg[] = "Hi, Mom";
	data_processed = write(file_descriptor2, msg, strlen(msg));
	printf("%d - wrote %d bytes\n", getpid(), data_processed);
	exit(EXIT_SUCCESS);
}
