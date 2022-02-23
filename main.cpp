#include "snp.h"
#include "HashTable.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool getSNP(ifstream&, snp*&);

int menu(void) {
	int input;
	cout << endl << "\tENTER MENU SELECTION:" << endl;
	cout << "0: EXIT" << endl;
	cout << "1: SHOW BY RSID" << endl;
	cout << "2: OPEN SNPEDIA BY RSID" << endl;
	cin >> input;
	return input;
}

int main() {
	HashTable Table = HashTable(50000);
	string file = "AncestryDNA.txt";
	ifstream input;
	input.open(file);
	if(!input.is_open()) {
		cout << "ERROR OPENING DNA FILE" << endl;
		return -1;
	}

	snp* newSNP;
	while(getSNP(input, newSNP)) {
		if(newSNP->getRS() != "NULL") {
			Table.put(newSNP);
		}
		if(newSNP->getRSCode() == 869031877) {
			break;
		}
	}
	int choice = menu();
	string rsid;
	while(choice != 0) {
		if(choice == 1) {
			cin >> rsid;
			newSNP = Table.find(rsid);
			if(newSNP == nullptr) {
				cout << "NOT FOUND" << endl;
			} else {
				newSNP->display();
			}
		} else if(choice == 2) {
			cin >> rsid;
			newSNP = Table.find(rsid);
			if(newSNP == nullptr) {
				cout << "NOT FOUND" << endl;
			} else {
				newSNP->display();
				newSNP->openSNPedia();
			}
		} else {
			cout << "INVALID CHOICE" << endl;
		}
		choice = menu();
	}
}


bool getSNP(ifstream& in, snp*& node) {
	string line;
	string inputString;
	string rs;
	unsigned rsCode;
	unsigned chromosome;
	unsigned position;
	string allele1;
	string allele2;
	getline(in,line);
	if(line.size() == 0 || line.at(0) == '#' || line.at(2) == 'i') {
		node = new snp("NULL",0,0,0,"","");
		return !in.eof();
	}
	stringstream currLine(line);
	getline(currLine,inputString,'\t');
	rs = inputString;
	rsCode = (unsigned)stoi(rs.substr(2));
	getline(currLine,inputString,'\t');
	chromosome = (unsigned)stoi(inputString);
	getline(currLine,inputString,'\t');
	position = (unsigned)stoi(inputString);
	getline(currLine,inputString,'\t');
	allele1 = inputString;
	getline(currLine,inputString,'\t');
	allele2 = inputString;
	node = new snp(rs, rsCode, chromosome, position, allele1, allele2);
	return !in.eof();
}