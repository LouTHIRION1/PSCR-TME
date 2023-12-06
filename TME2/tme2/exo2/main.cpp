#include<iostream>
#include<string>

#include "HashMap.h"

using namespace std;

int main() {
	
	pr::HashTable<string, int> h(5);
	
	h.put("bonjour", 3678);
	h.put("salut", 4);
	
	cout<<*h.get("salut")<<endl;
}
