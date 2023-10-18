#include <thread>
#include <iostream>

#include "Banque.h"

using namespace std;

const int NB_COMPTE = 100000;
const int NB_THREAD = 10000;
const int CREDIT = 10000;

void crash_banque(pr::Banque & b) {
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	for(int k = 0; k<1000; k++){
		int i = std::rand()%NB_COMPTE;
		int j = std::rand()%(NB_COMPTE-i)+i;
		int m = std::rand()%100;
		int dodo = std::rand()%20;
		b.transfert(j, i, m);
		//cout<<"dodo"<<endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(dodo));
	}
}

int main () {


	pr::Banque b(NB_COMPTE, CREDIT);

	vector<thread> threads;
	threads.reserve(NB_THREAD);
	// creer des threads qui font ce qui est demandé
	cout << "creation des threads." << endl;
	for(int i = 0; i<NB_THREAD; i++) {
		threads.emplace_back(crash_banque, std::ref(b));
	}

	for (auto & t : threads) {
		t.join();
	}

	cout << "threads tous terminés." << endl;

	// TODO : tester solde = NB_THREAD * JP
	if(b.comptabiliser(NB_COMPTE*CREDIT))
		cout<<"la compta est bonne !"<<endl;
	else
		cout<<"ERREUR DANS LA COMPTA !!!" << endl;

	return 0;
}


