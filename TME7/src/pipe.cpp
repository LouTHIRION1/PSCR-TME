#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


using namespace std;

int main(int argc, char **argv) {

	int tube[2];
	pipe(tube);

	if(argc < 1){
		perror("Pas d'arguments");
		return 1;
	}

	execl("/bin/echo", "mqjfhdpiqufh", NULL);
	cout << argc <<endl;
	for (int i = 0; i< argc; i++){
		cout << argv[i] << endl;
	}
	int i = 2;
	char * mesargs[argc-2];
	for(;i<argc; i++) {
		mesargs[i-2] = argv[i];
		cout << argv[i]<<endl;
	}
	execv(argv[1], mesargs);
	return 0;

	/*char* cmd1;
	char* args_cmd1[];
	int i_1 = 0;
	char* cmd2;
	char* args_cmd2[];
	int i_2 = 0;
	bool pipe = false;
	for(int i = 0; i<argc; i++) {
		if(argc[i]=="|")
			pipe = true;
		if(pipe)
			args_cmd2[i_2++] = argc[i];
		else
			args_cmd1[i_1++] = argc[i];
	}*/

	/*char* cmd1 = "/bin/cat";
	char* args_cmd1[] = {"pipe.cpp"};
	char* cmd2 = "/bin/wc";
	char* args_cmd2[] = {"-l"};*/

	if(fork()==0) {
		dup2(tube[1],STDOUT_FILENO);
		//execv(cmd1,args_cmd1);
		execl("/bin/cat", "pipe.cpp", NULL);
		close(tube[0]);
		close(tube[1]);
		return 0;

	}else if(fork()==0) {
		dup2(tube[0],STDIN_FILENO);
		//execv(cmd2,args_cmd2);
		execl("/bin/wc", "-l", NULL);
		close(tube[0]);
		close(tube[1]);
		return 0;
	}

	wait(0);
	wait(0);
}
