//Mason Kimbell
//MyMv.c
//works the same as the mv command
//03/11/2020

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv){
	if(argc < 3){
		printf("not enough params");
		return 1;
	}
	//argv1 = file name
	//argv2 = destination name

	//combine cwd and argv[1]
	//need to do this to get the first path argument used in link()
	char cwd[100];
	if(getcwd(cwd, sizeof(cwd)) == NULL){
		printf("error");
	}
	int i = 0;
	while(cwd[i] != '\0')
		i++;
	cwd[i] = '/';
	i++;
	int j;
	for(j = 0; j < sizeof(argv[1]); j++){
		cwd[i] = argv[1][j];
		i++;
	}
	cwd[i] = '\0';
	//done combining
	
	//printf("attempting to link %s with %s...\n", cwd, argv[2]);
	if(link(cwd, argv[2]) < 0){ //case 1: pass a path with a file name
		//printf("link error");
		//printf("attempting case 2...\n");
		
		//case 2: just pass a path
		//combine argv[2] and argv[1]
		int k = 0;
		char combined[100];
		while(argv[2][k] != '\0'){
			combined[k] = argv[2][k];
			k++;
		}
		combined[k] = '/';
		k++;
		int l;
		for(l = 0; l < sizeof(argv[1]); l++){
			combined[k] = argv[1][l];
			k++;
		}
		combined[k] = '\0';
		//printf("attempting to link %s with %s...\n", cwd, combined);
		if(link(cwd, combined) < 0){
			printf("link error\n");
			return 1;
		}
	}
	unlink(cwd);
	return 0;
}
