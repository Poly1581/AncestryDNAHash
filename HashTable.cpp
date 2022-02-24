#include "HashTable.h"
#include "snp.h"
#include "math.h"

/* HashTable constructor
*/
HashTable::HashTable (int s) {
	size = s;
	hashTable = new list<snp>[size];
}

/* contains
*  Takes RSID string as input and checks whether or not 
*  the hash table contains an SNP with that RSID by searching
*/
bool HashTable::contains(const string &s) {
	return !(find(s)==nullptr);
}

/* put
*  add snp to table by computing hash and adding in the correct place
*/
void HashTable::put(snp* node) {
	int hash = computeHash(node->getRS());
	snp* word= find(node->getRS());
	if(word == nullptr) {
		hashTable[hash].push_back(*node);
	}
}

/* find
*  Takes RSID string and finds the corresponding
*  SNP (if it exists) in the table
*/

snp* HashTable::find(const string&s) {
	int hash = computeHash(s);
	for(auto& node : hashTable[hash]) {
		if(node.getRS() == s) {
			return &node;
		}
	}
	return nullptr;
}

/* getRandom
*  find a random SNP
*/

snp* HashTable::getRandom(void) {
	int rHash = rand()%size;
	list<snp> bucket = hashTable[rHash];
	while(bucket.size() == 0) {
		rHash = rand()%size;
		bucket = hashTable[rHash];
	}
	int rPos = rand()%bucket.size();
	for(auto& node : hashTable[rHash]) {
		if(rPos == 0) {
			return &node;
		}
		rPos--;
	}
	return nullptr;
}


/* computeHash
*  compute the hash of a given RSID string
*  by iterating over it and XORing it in different ways
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