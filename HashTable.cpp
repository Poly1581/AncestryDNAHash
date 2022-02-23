#include "HashTable.h"
#include "snp.h"
#include "math.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
	size = s;
	hashTable = new list<snp>[size];
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string& s) {
	int hash = 0;
	for(unsigned i = 0; i < s.size(); i+=2) {
		hash = (hash << 2) ^ s.at(i);
		hash = hash % size;
	}
	for(unsigned i = 0; i < s.size(); i+=2) {
		hash = (hash << 5) ^ (s.at(i) << 3);
		if(i+1 < s.size()) {
			hash = hash ^ (s.at(i+1));
		}
		hash = hash % size;
	}
	return hash % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(snp* node) {
	int hash = computeHash(node->getRS());
	snp* word= find(node->getRS());
	if(word == nullptr) {
		hashTable[hash].push_back(*node);
	}
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
	return !(find(s)==nullptr);
}

snp* HashTable::find(const string&s) {
	int hash = computeHash(s);
	for(auto& node : hashTable[hash]) {
		if(node.getRS() == s) {
			return &node;
		}
	}
	return nullptr;
}