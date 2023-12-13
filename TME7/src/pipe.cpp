#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		perror("Pas d'arguments");
		return 1;
	}

	char *cmd1 = argv[1];
	char *cmd2;
	char **args1 = argv + 1;
	char *args2[argc];
	memset(args2, 0, argc * sizeof(char *));

	int i, cpt;
	for (i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "|") == 0)
		{
			cmd2 = argv[i + 1];
			argv[i] = NULL;
			cpt = i + 1;
			break;
		}
	}
	for (i = 0; i < cpt; i++)
	{
		printf("test %s\n", argv[i + cpt]);
		args2[i] = argv[i + cpt];
	}

	// printf("cmd1 : %s\n", cmd1);
	char **args = args1;
	while (*args != nullptr)
	{
		printf("args1 : %s\n", *(args++));
	}
	// printf("cmd2 : %s\n", cmd2);
	args = args2;
	while (*args != nullptr)
	{
		printf("args2 : %s\n", *(args++));
	}

	// char *params[] = {"/usr/bin/ls", "-l", NULL};
	// execv(params[0],params);
	/*if(execv(args1[0], args1)){
		perror("execv error");
		exit(1);
	}*/

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
	int tube[2];
	if (pipe(tube) == -1)
	{
		perror("erreur pipe");
		exit(1);
	}
	int pid;
	if (pid = fork() == 0)
	{
		std::cout << "TEST BONJOUR" << std::endl;
		// std::cout << dup2(tube[1], STDOUT_FILENO) << std::endl;
		dup2(tube[1], STDOUT_FILENO);
		// execv(cmd1,args_cmd1);
		close(tube[1]);
		close(tube[0]);
		if (execv(args1[0], args1) == -1)
		{
			perror("erreur execv fils");
			exit(1);
		}
		std::cout << "fils fait" << std::endl;
		return 0;
	}
	else if (pid != -1)
	{
		//}else if(fork()==0) {
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
		close(tube[1]);
		// execv(cmd2,args_cmd2);
		if (execv(args2[0], args2) == -1)
		{
			perror("execv père");
			exit(1);
		}
		std::cout << "père fait" << std::endl;
	}
	else
	{
		perror("erreur fork");
		exit(2);
	}

	wait(0);
}
