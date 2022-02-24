#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include "snp.h"

using namespace std;


class HashTable {

 private:
	list<snp> *hashTable;
	int size;

 public:
	HashTable(int);
	bool contains(const string &);
	void put(snp*);
	snp* find(const string&);
	snp* getRandom(void);

 private:
	int computeHash(const string&);
};

#endif