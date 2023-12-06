#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <utility>

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	vector<pair<string, int>> vec;
	int cpt;
	
	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		
		cpt = 0;
		for(auto & p : vec) {
			if(p.first == word) {
				++p.second;
				break;
			}
			++cpt;
		}
		if(cpt == vec.size())
			vec.push_back(pair<string, int>(word, 1));
		
		
		
		// word est maintenant "tout propre"
		if (nombre_lu % 10000 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    
    string w = "toto";
    auto nbw = find_if(vec.begin(), vec.end(), [w](pair<string, int> p){return p.first == w;});
    //for(auto & p : vec)
	  //  cout << p.first << " " << p.second <<endl;
    cout << "le mot " << w << " a été trouvé " << (*nbw).second << " fois." << endl;

    return 0;
}


