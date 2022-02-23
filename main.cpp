#include "snp.h"
#include "HashTable.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool getSNP(ifstream&, snp*&);

string menu(void) {
	string input;
	cout << endl << "\tENTER MENU SELECTION:" << endl;
	cout << "EXIT" << endl;
	cout << "SHOW: SEARCH BY RSID" << endl;
	cout << "OPEN: OPEN RSID PAGE IN SNPEDIA" << endl;
	getline(cin,input);
	for(unsigned i = 0; i < input.size(); i++) {
		input.at(i) = tolower(input.at(i));
	}
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
	string choice = menu();
	string rsid;
	int RSCode;
	while(choice != "exit") {
		if(choice == "show") {
			getline(cin,rsid);

			while(rsid.size() == 0) {
				cout << "ERROR READING RSID, PLEASE ENTER AGAIN" << endl;
				getline(cin,rsid);
			}

			if(rsid.at(0) == 'r') {
				newSNP = Table.find(rsid);
			} else {
				newSNP = Table.find("rs"+rsid);
			}

			if(newSNP == nullptr) {
				cout << "NOT FOUND" << endl;
			} else {
				newSNP->display();
			}
		} else if(choice == "open") {
			getline(cin,rsid);

			if(rsid.at(0) == 'r') {
				newSNP = Table.find(rsid);
			} else {
				newSNP = Table.find("rs"+rsid);
			}

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