#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//run with (./Task1 < inputFileName) > outputFileName

int main(){

//read file byte by byte
char b[1];

//while one byte is read from std input, write one byte to std output
//continue until no bytes are read
//reads one at a time

while((read(0, &b, 1) > 0))
	write(1, &b, 1);

return 0;

}
