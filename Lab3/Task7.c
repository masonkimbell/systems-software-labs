#include <stdio.h>

int str_to_int(char *str){
	int sum = 0;
	int i = 0;
	while(str[i] != '\0'){
		sum = 10 * sum + (str[i] - '0');
		i++;
	}
	return sum;
}

int main(int argc, char** argv){
	if(argc < 2){
		printf("error: no args passed\n");
		return 1;
	}

	int i;
	int sum = 0;
	for(i = 1; i < argc; i++){
		sum += str_to_int(argv[i]);
	}
	printf("the sum of the params is %d\n", sum);
}
