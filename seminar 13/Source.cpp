#include <iostream>
using namespace std;

class Aplicatie
{
private:
	const double IDUnic;
	bool inMemoriaTelefonului;
	int nrZileUtilizare;
	int* nrAccesariZilnice;
	static int valoareStatica;
	bool boolCareLipseste;
public:
	//implementare constructori
	Aplicatie() :IDUnic(0) {
		this->inMemoriaTelefonului = false;
		this->nrZileUtilizare = 0;
		this->nrAccesariZilnice = NULL;
		this->boolCareLipseste = false;
	}

	//constructor cu parametri
	//sunt validate datele de intrare
	//pentru date de intrare invalide se genereaza exceptie  - vezi exemplu mai jos
	Aplicatie(bool inMemoriaTelefonului, int nrZileUtilizare, int* nrAccesariZilnice) :IDUnic(valoareStatica) {
		if (inMemoriaTelefonului == true) {
			this->inMemoriaTelefonului = inMemoriaTelefonului;
		}
		else {
			throw exception("Eroare inMemoriaTelefonului");
		}
		if (nrZileUtilizare > 2) {
			this->nrZileUtilizare = nrZileUtilizare;
		}
		else {
			throw "Eroare in nrZileUtilizare";
		}
		if (nrAccesariZilnice != NULL) {
			this->nrAccesariZilnice = new int[nrZileUtilizare];
			for (int i = 0; i < nrZileUtilizare; i++) {
				this->nrAccesariZilnice[i] = nrAccesariZilnice[i];
			}
		}
		else {
			throw "Eroare in nrAccesariZilnice";
		}
		this->boolCareLipseste = false;
	}

	//implementare constructor de copiere
	Aplicatie(const Aplicatie &a) :IDUnic(a.IDUnic) {
		this->boolCareLipseste = a.boolCareLipseste;
		this->inMemoriaTelefonului = a.inMemoriaTelefonului;

		this->nrZileUtilizare = a.nrZileUtilizare;
		this->nrAccesariZilnice = new int[nrZileUtilizare];
		for (int i = 0; i < nrZileUtilizare; i++) {
			this->nrAccesariZilnice[i] = a.nrAccesariZilnice[i];
		}
	}

	//implementare destructor
	~Aplicatie() {
		if (this->nrAccesariZilnice != NULL) {
			delete[] this->nrAccesariZilnice;
		}
	}

	//implementare diferite metode

	//metoda ce returneaza numarul de zile de utilizare a aplicatiei
	int getNrZileUtilizare() {
		return this->nrZileUtilizare;
	}

	//metoda ce returneaza loatia aplicatiei - true pentru memoria telefonului sau false daca este pe card
	bool getInMemoriaTelefonului() {
		return this->inMemoriaTelefonului;
	}

	//metoda ce adauga o noua zi de utilizare a aplicatiei
	void adaugaONouaZi() {
		this->nrZileUtilizare++;
		int *temp = new int[nrZileUtilizare];
		for (int i = 0; i < this->nrZileUtilizare - 1; i++) {
			temp[i] = this->nrAccesariZilnice[i];
		}
		temp[nrZileUtilizare - 1] = 0;

		if (this->nrAccesariZilnice != NULL) {
			delete[] this->nrAccesariZilnice;
		}
		this->nrAccesariZilnice = temp;
	}

	//metoda ce determina ziua in care aplicatia a avut un maxim de accesari
	//daca sunt mai multe zile cu acelasi numar maxim de accesari atunci se intoarce indexul primei zile
	int getZiCuMaximUtilizari() {
		int maxim = -1;
		int index = -1;
		for (int i = 0; i < nrZileUtilizare; i++) {
			if (this->nrAccesariZilnice[i] > maxim) {
				maxim = this->nrAccesariZilnice[i];
				index = i;
			}
		}
		return index;
	}

	//metoda inregistreaza o noua accesare a aplicatiei pentru ziua curenta
	void accesareAplicatie() {
		this->nrAccesariZilnice[this->nrZileUtilizare - 1]++;
	}

	//nu sterge aceasta metoda
	int* getNrAccesariZilnice() {
		return this->nrAccesariZilnice;
	}

	//operatori

	Aplicatie &operator=(const Aplicatie &a) {
		if (this->nrAccesariZilnice != NULL) {
			delete[] this->nrAccesariZilnice;
		}

		this->boolCareLipseste = a.boolCareLipseste;
		this->inMemoriaTelefonului = a.inMemoriaTelefonului;

		this->nrZileUtilizare = a.nrZileUtilizare;
		this->nrAccesariZilnice = new int[nrZileUtilizare];
		for (int i = 0; i < nrZileUtilizare; i++) {
			this->nrAccesariZilnice[i] = a.nrAccesariZilnice[i];
		}

		return *this;
	}

	friend ostream &operator<<(ostream &out, Aplicatie a) {
		out << " Bool care lipseste: " << a.boolCareLipseste << " In memoria telefonului: "
			<< a.inMemoriaTelefonului << " Nr. zile utilizare: " << a.nrZileUtilizare
			<< " IDUnic: " << a.IDUnic << " Valoare statica: " << a.valoareStatica
			<< " Accesari zilnice: ";
		for (int i = 0; i < a.nrZileUtilizare; i++) {
			out << a.nrAccesariZilnice[i] << " ";
		}
		out << endl;
		return out;
	}

	friend istream &operator>>(istream &in, Aplicatie &a) {
		cout << "Bool care lipseste: "; in >> a.boolCareLipseste;
		cout << "In memoria telefonului: "; in >> a.inMemoriaTelefonului;
		cout << "Nr. zile utilizare: "; in >> a.nrZileUtilizare;
		cout << "Accesari zilnice: ";
		if (a.nrAccesariZilnice != NULL) {
			delete[] a.nrAccesariZilnice;
		}
		a.nrAccesariZilnice = new int[a.nrZileUtilizare];
		for (int i = 0; i < a.nrZileUtilizare; i++) {
			in >> a.nrAccesariZilnice[i];
		}
		return in;
	}
	bool operator!() {
		this->boolCareLipseste = !this->boolCareLipseste;
		return this->boolCareLipseste;
	}
	explicit operator int() {
		int suma = 0;
		for (int i = 0; i < this->nrZileUtilizare; i++) {
			suma += nrAccesariZilnice[i];
		}
		return suma;
	}
};

int Aplicatie::valoareStatica = 1000;

/*

//exemplu generare exceptie ce arunca un string
throw "Mesaj eroare";

*/

//testeaza metodel in main()

int main() {
	Aplicatie a1;
	cout << "a1=\n";
	cout << a1.getInMemoriaTelefonului() << endl;
	cout << a1.getNrZileUtilizare() << endl;

	int a[] = { 5,10,15 };
	Aplicatie a2(true, 3, a);
	cout << "a2=\n" << a2;

	a2.adaugaONouaZi();
	cout << "Adaugare zi noua:\n" << a2;

	Aplicatie a3(a2);
	cout << "Const. copiere\n" << a3;

	a3.accesareAplicatie();
	cout << "Dupa accesare aplicatie:\n" << a3;
	cout << "Ziua cu maxim utilizari din a3: " << a3.getZiCuMaximUtilizari() << endl;

	//op. =
	cout << "op =\n";
	Aplicatie a4;
	a4 = a3;
	cout << a4;


	//op. !
	cout << "Activeaza sau dezactiveaza protectia pentru copii: " << !a4;
	cout << "\ndin nou a4\n" << a4;

	//op. cast int
	int suma = (int)a3;
	cout << "Numarul total de accesari pentru intreaga " << suma << endl;

	//op. >>
	cout << "op >> \n";
	Aplicatie a5;
	cin >> a5;
	cout << a5;
}