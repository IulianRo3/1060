#include<iostream>
#include<string>

using namespace std;
class IAfisare {
public:
	const string codBadge = "XY2xss-mnckMGJ-dkada";
	virtual void afisareInformatii() = 0;
};
class Angajat :public IAfisare {
protected:
	string nume;
public:
	int varsta;
	double salariu;

	Angajat() {
		this->nume = "Angajat Anonim";
		this->varsta = 26;
		this->salariu = 3000.5;
	}
	Angajat(string nume, int varsta, double salariu) {
		this->nume = nume;
		this->varsta = varsta;
		this->salariu = salariu;
	}
	void afisareInformatii() {
		cout << "Angajat => Nume: " << this->nume
			<< " Varsta: " << this->varsta << " Salariu: "
			<< this->salariu;
	}

	virtual void marireSalariala() = 0;
};

class Manager :public Angajat, IAfisare {
public:
	bool areMasina;

	Manager() {
		this->areMasina = false;
	}

	Manager(string nume, int varsta, double salariu,
		bool areMasina) :Angajat(nume, varsta, salariu) {
		this->areMasina = areMasina;
	}
	void afisareInformatii() {
		Angajat::afisareInformatii();
		if (this->areMasina == true) {
			cout << ";;Manager = > Are masina : DA\n";
		}
		else {
			cout << ";;Manager => Are masina: NU\n";
		}
	}
	void marireSalariala() {
		this->salariu += 3000;
	}
};

class Inginer :public Angajat, IAfisare {
public:
	bool stieProgramare;
	Inginer() :Angajat("Inginer Anonim", 34, 5000) {
		this->stieProgramare = false;
	}
	Inginer(string nume, int varsta, double salariu,
		bool stieProgramare) :Angajat(nume, varsta, salariu) {
		this->stieProgramare = stieProgramare;
	}
	void afisareInformatii() {
		Angajat::afisareInformatii();
		if (this->stieProgramare == true) {
			cout << ";;Inginer => Stie programare: DA\n";
		}
		else {
			cout << ";;Inginer = > Stie programare : NU\n";
		}
	}
	void marireSalariala() {
		this->salariu += 500;
	}
};

class Companie {
public:
	string denumire;
	Angajat **listaAngajati;
	int nrAngajati;

	Companie() {
		this->denumire = "Companie fantoma";

		this->nrAngajati = 2;

		this->listaAngajati = new Angajat*[this->nrAngajati];
		for (int i = 0; i < this->nrAngajati; i++) {
			this->listaAngajati[i] = new Inginer();
		}
	}

	Companie(string denumire, Angajat **listaAngajati, int nrAngajati) {
		this->denumire = denumire;

		this->nrAngajati = nrAngajati;

		this->listaAngajati = new Angajat*[nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->listaAngajati[i] = listaAngajati[i];
		}
	}

	~Companie() {
		if (listaAngajati != NULL) {
			for (int i = 0; i < this->nrAngajati; i++) {
				delete this->listaAngajati[i];//se dezaloca elemente
			}
			delete[] this->listaAngajati;
		}
	}

	void afisareInformatiiAngajat(int index) {
		listaAngajati[index]->afisareInformatii();
	}
};
int main() {
	//cout << boolalpha << true;
	//Angajat a;
	//a.afisareInformatii();
	//cout << endl;

	Manager m;
	m.afisareInformatii();

	Inginer i;
	i.afisareInformatii();

	//clase abstracte
	cout << "Clase abstracte\n";
	Angajat *ap = new Inginer();

	Manager *mp = new Manager("Ioana", 30, 12000, true);
	m.afisareInformatii();

	Inginer *ip = new Inginer("Rares", 24, 3000, false);
	i.afisareInformatii();

	//override fct pura marire salariu /polimorfism
	cout << "\n\n polimorfism prin upcasting pt marire salariu\n";
	Angajat *aaa1 = mp;
	aaa1->marireSalariala();
	aaa1->afisareInformatii();

	Angajat *aaa2 = ip;
	aaa2->marireSalariala();
	aaa2->afisareInformatii();

	cout << "Companie:\n\n\n";
	Angajat **listaAngajati = new Angajat*[3]{ ap,mp,ip };
	Companie *c1 = new Companie();
	Companie *c2 = new Companie("Systematic", listaAngajati, 3);

	cout << "Polimorfism prin functia afisareInformatiiAngajat\n\n";//adica cand faci afisare pentru lista de angajati din companie se apeleaza metoda din copii
	for (int i = 0; i < 3; i++) {
		c2->afisareInformatiiAngajat(i);
	}
}