#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main2 () {
	const int N = 3;
	int mainpid = getpid();
	std::cout << "main pid=" << getpid() << std::endl;
	int nbFils = 0;

	for (int i=1, j=N; i<=N && j==N; i++ ) {
		if(fork()==0) {
			nbFils = 0;
			std::cout << " i:j " << i << ":" << j << std::endl;
			for (int k=1; k<=i && j==N ; k++) {
				if ( fork() == 0) {
					nbFils = 0;
					j=0;
					std::cout << " k:j " << k << ":" << j << std::endl;
				}else {
					nbFils++;
				}
			}
		}else {
			nbFils++;
			break;
		}
	}

	for(int i = 0;i<nbFils;i++) {
		std::cout << "1" << std::endl;
		wait(nullptr);
	}

	return 0;
}
