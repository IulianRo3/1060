#include<iostream>
using namespace std;
class Masina {
private:
	const int cod;
public:
	char *culoare;
	int an;
	static int nrMasina;

	Masina() :cod(0) {
		this->an = 0;
		this->culoare = NULL;
	}

	Masina(char *culoare1, int an1):an(an1),cod(nrMasina) {
		this->culoare = new char[strlen(culoare1) + 1];
		strcpy(this->culoare, culoare1);
	}

	Masina(int an);

	Masina(Masina &masinaNoua);

	int getCod() {
		return this->cod;
	}

	void afisare1() {
		cout << an << " " << nrMasina << endl;
	}
	void afisare2() {
		cout << "cod: " << cod
			<< " an: " << an
			<< " culoare: " << culoare
			<< " nrMasina: " << nrMasina << endl;
	}

	~Masina() {
		if (culoare != NULL) {
			delete[]culoare;
		}
	}
};
int Masina::nrMasina = 100;

Masina::Masina(Masina &masinaNoua) :cod(masinaNoua.cod) {
	this->nrMasina = masinaNoua.nrMasina;
	this->an = masinaNoua.an;
	this->culoare = new char[strlen(masinaNoua.culoare) + 1];
	strcpy(this->culoare, masinaNoua.culoare);
}

Masina::Masina(int an1):cod(nrMasina) {
	this->an = an1;
	this->culoare = NULL;
}

int main() {
	cout << "merge" << endl;

	cout << "m1:" << endl;
	Masina m1;
	m1.afisare1();
	m1.nrMasina++;

	cout << "m2:\n";
	char culoareRosie[] = { "rosu" };
	Masina m2(culoareRosie, 2019);
	m2.nrMasina++;
	cout << "m1:\n";
	m1.afisare1();
	cout << "m2:\n";

	m2.afisare2();
	//obiecte legate cu pointeri
	Masina *m3;
	m3 = new Masina();
	char culoareVerde[] = { "verde" };
	Masina *m4 = new Masina(culoareVerde, 2018);

	cout << "Apelare getter pentru un obiect Masina dinamic:"
		<< m4->getCod() << endl;


	cout << "\n\nm4" << endl << endl;
	m4->afisare2();

	///apelare constructor de copiere
	cout << "m5" << endl << endl;
	Masina m5(*m4);
	m5.an = 2010;
	m5.afisare2();
}