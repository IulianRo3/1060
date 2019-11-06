#include<iostream>
using namespace std;

//practic declari ca exista 2 clase Departament si Angajat
class Departament;
class Angajat;


class Departament {
private:
	int nrDepartament;
public:
	void afisareDepartament(Angajat a);
};

class Angajat {
private:
	char *nume;
	double salariu;
public:
	Angajat() {
		this->nume = NULL;
	}

	Angajat(const char *nume, double salariu) {
		this->salariu = salariu;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}

	Angajat(const Angajat &angajatNou) {
		this->salariu = angajatNou.salariu;
		this->nume = new char[strlen(angajatNou.nume) + 1];
		strcpy(this->nume, angajatNou.nume);
	}
	~Angajat() {
		if (this->nume != NULL) {
			delete[] this->nume;
		}
	}
	void afisare() {
		cout << "Nume angajat: " << this->nume << " ;salariu: "
			<< this->salariu << endl;
	}
	//supraincarcare
	void suma(Angajat a) {//aici se apeleaza 
		//constr de copiere Angajat.

		cout << "Suma angajati: " <<
			this->salariu + a.salariu << endl;
	}
	int suma(int a, int b) {
		return a + b;
	}
	double suma(int a, float b) {
		return a + b;
	}

	void suma(const char *mesaj) {
		cout << mesaj << endl;
	}

	//clasa friend
	friend class Companie;
	//functii friend ale unei clase;
	friend void Departament::afisareDepartament(Angajat a);
	//functie globala friend
	friend void afiseazaBunaDimineataPentruUnAngajat(Angajat a);
};

void Departament::afisareDepartament(Angajat a) {
	cout << "Departament cu angajat: " << a.nume << endl;
}

class Companie {
private:
	int bugetCompanie;
public:
	Companie(int bugetCompanie) {
		this->bugetCompanie = bugetCompanie;
	}
	void afisareAngajatDinCompanie(Angajat a) {//aici se apeleaza 
		//constr de copiere Angajat.
		cout << "Compania are bugetul: " << bugetCompanie
			<< " si angajatul: " << a.nume<<endl;
	}
};

void afiseazaBunaDimineataPentruUnAngajat(Angajat a) {
	cout << "Buna dimineata, " << a.nume << " cu salariul: "
		<< a.salariu << endl;;
}

int main() {
	cout << "merge" << endl;
	Angajat a1;
	Angajat a2("Rares", 2000);
	a2.afisare();

	cout << "\nSupraincarcare metoda suma" << endl;
	Angajat a3("Mihai", 1000);
	
	//supraincarcare metoda void
	a3.suma(a2);

	//supraincarcare metoda int a, int b
	int a = 10, b = 20;
	a3.suma(a, b);

	//supraincarcare metoda int a, float b
	float x = 100;
	int y = 200;
	a3.suma(y, x);

	//supraincarcare metoda char *mesaj
	a3.suma("Acesta este un mesaj pentru a demostra suprascrierea");
	
	Angajat a4(a3);
	Angajat a5 = a4;
	//Angajat a6;
	//a6 = a4; //aici se apeleaza operatorul egal daca l-am fi definit
	
	//apelare functii si clase friend
	Companie c(20000);
	c.afisareAngajatDinCompanie(a5);

	afiseazaBunaDimineataPentruUnAngajat(a2);
}