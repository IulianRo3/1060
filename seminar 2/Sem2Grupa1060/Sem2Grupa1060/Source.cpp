#include<iostream>
using namespace std;

class Persoana {
private:
	char *CNP;
protected:
public:
	char *nume;
	int varsta;

	Persoana() {
		this->nume = NULL;
		this->varsta = NULL;
		this->CNP = NULL;
	}

	Persoana(char* nume1, int varsta1) {
		this->nume = new char[strlen(nume1) + 1];
		strcpy(this->nume, nume1);
		this->varsta = varsta1;
		this->CNP = NULL;
	}
	Persoana(char* nume1, int varsta1, char* CNP1) {
		this->nume = new char[strlen(nume1) + 1];
		strcpy(this->nume, nume1);
		this->varsta = varsta1;
		this->CNP = new char[strlen(CNP1) + 1];
		strcpy(this->CNP, CNP1);
	}
	~Persoana() {
		if (CNP != NULL) {
			delete[] CNP;
		}
		if (nume != NULL) {
			delete[] nume;
		}
	}

	int getVarsta() {
		return varsta;
	}
	void setVarsta(int nouaVarsta) {
		this->varsta = nouaVarsta;
	}
};

int main() {
	cout << "merge";

	Persoana p1;

	char nume2[] = { "Rares" };

	char nume3[] = { "Alex" };
	char CNP[] = { "12212121" };

	Persoana p2(nume2, 19);
	Persoana p3(nume3, 20, CNP);
	p3.setVarsta(30);
	cout << endl << p3.varsta << endl;
	cout << p3.getVarsta() << endl;
	Persoana p4;



}