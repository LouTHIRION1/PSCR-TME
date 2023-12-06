#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


using namespace std;

int main3(int argc, char **argv) {

	if(argc < 1){
		perror("Pas d'arguments");
		return 1;
	}

	cout << argc <<endl;
	for (int i = 0; i< argc; i++) cout << argv[i];
	execl("/bin/echo", "bonjour", NULL);
	int i = 2;
	char * mesargs[argc-2];
	for(;i<argc; i++) {
		mesargs[i-2] = argv[i];
		cout << argv[i]<<endl;
	}
	execv(argv[1], mesargs);
	return 0;
}
