#ifndef SNP_H
#define SNP_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class snp {
	public:
		snp(const string& r, unsigned rc, unsigned short c, unsigned p, const string& a1, const string& a2) :
			rs(r), rsCode(rc), chromosome(c), position(p), allele1(a1), allele2(a2){};

		string getRS(void) {return rs;};
		unsigned getRSCode(void) {return rsCode;};
		unsigned getChromosome(void) {return chromosome;};
		unsigned getPosition(void) {return position;};
		string& getAllele1(void) {return allele1;};
		string& getAllele2(void) {return allele2;};

		void openSNPedia(void) {
			string command = "google-chrome www.snpedia.com/index.php/Rs" + rs.substr(2);
			system(command.c_str());
		};
		void display(void) {
			cout << "GENE: " << rs << endl;
			cout << "\tCODE: " << rsCode << endl;
			cout << "\tCHROMOSOME: " << chromosome << endl;
			cout << "\tPOSITION: " << position << endl;
			cout << "\tALLELES: " << allele1 << " " << allele2 << endl;
		};
	private:
		string rs;
		unsigned rsCode;
		unsigned chromosome;
		unsigned position;
		string allele1;
		string allele2;
};

#endif