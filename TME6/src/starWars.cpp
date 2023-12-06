#include <iostream>
//#include <unistd>
#include <sys/wait.h>
#include <csignal>
#include "rsleep.h"
#include <string>
#include <ctime>

int PV = 10;
std::string nom;

void attaque (pid_t adversaire) {
	signal(SIGINT, [](int){
		PV--;
		std::cout << nom << " points de vie restants : " << PV << std::endl;
		if(PV==0){
			std::cout << nom << " est mort !!" << std::endl;
			exit(1);
		}
	});

	if(kill(adversaire, SIGINT)<0) {
		std::cout << "il est mort " << adversaire << std::endl;
		exit(0);
	}

	randsleep();
}

void defense() {
	signal(SIGINT, SIG_IGN);
	randsleep();
}

void combat(pid_t adversaire) {
	while(true){
		defense();
		attaque(adversaire);
	}
}


void defenseLuke() {
	signal(SIGINT, SIG_IGN);
	randsleep();
}

void combatLuke(pid_t adversaire) {
	while(true){
		defenseLuke();
		attaque(adversaire);

	}
}

int main(){

	pid_t dark_vador = getpid();
	nom = "Dark Vador";

	pid_t luke = fork();
	std::srand(std::time(nullptr));
	if(luke==0){
		nom = "Luke";
		combat(dark_vador);
	}
	else{
		combat(luke);
	}

	return 0;
}
