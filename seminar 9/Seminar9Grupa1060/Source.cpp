#include<iostream>
#include<string>

using namespace std;

// asa se defineste o interfata....
class A {
	virtual void metodaPura1() = 0;
	virtual void metodaPura2() = 0;

};

class Autovehicul{
private:
	int nrRoti;
protected:
	bool masinaAutomata;
public:
	string marca;
	Autovehicul() {

	}
	Autovehicul(int nrRoti, bool masinaAutomata, string marca) {
		this->nrRoti = nrRoti;
		this->masinaAutomata = masinaAutomata;
		this->marca = marca;
	}
	void metodaOarecare();

	void afisareAutovehicul() {
		cout << "Autovehicul: " << "Nr. roti: " << this->nrRoti
			<< " e masina automata: " << this->masinaAutomata
			<< " Marca: " << this->marca;
	}

	virtual void metodaSuprascrisa() {
		cout << "Esti in clasa Autovehicul\n";
	}

};
void Autovehicul::metodaOarecare() {
	cout << "A fost apelata metoda oarecare din clasa Autovehicul\n";
}
//TRACTOR = AUTOVEHICUl + arePlug si toate metodele publice
class Tractor :public Autovehicul {
public:
	bool arePlug;
	Tractor(bool arePlug) :Autovehicul(4, false, "ROMAN") {
		this->arePlug = arePlug;
	}

	void metodaOarecare() {
		cout << "A fost apelata metoda oarecare din clasa Tractor\n";
	}
	void afisareTractor() {
		afisareAutovehicul();
		cout << " Tractor: " << " Are Plug:" << arePlug << endl;
	}
	void metodaSuprascrisa() {
		cout << "Esti in clasa Tractor\n";
	}
};

class Motocicleta :public Autovehicul {
public:
	bool faceZgomot;

	Motocicleta(bool faceZgomot, int nrRoti, bool masinaAutomata, string marca)
		:Autovehicul(nrRoti, masinaAutomata, marca) {
		this->faceZgomot = faceZgomot;
	}

	void metodaOarecare() {
		cout << "A fost apelata metoda oarecare din clasa Motocicleta\n";
	}

	void afisareMotocicleta() {
		afisareAutovehicul();
		cout << " Motocicleta: " << " Face zgomot:" << faceZgomot << endl;
	}

	void metodaSuprascrisa() {
		cout << "Esti in clasa Motocicleta\n";
	}
};

int main() {
	Autovehicul a1(4, true, "Audi");
	a1.afisareAutovehicul();
	cout << endl;
	a1.metodaOarecare();
	cout << endl;
	Tractor t1(true);
	t1.afisareTractor();
	t1.metodaOarecare();
	cout << endl;
	Motocicleta m1(true, 2, true, "Kawasaki");
	m1.metodaOarecare();
	m1.afisareMotocicleta();
	cout << endl;


	cout << "UPCASTING - early binding\n";
	cout << endl;
	Autovehicul a2;
	//copilul poate fi atribuit parintelui
	a2 = m1;
	a2.afisareAutovehicul();
	cout << endl;
	a2.metodaOarecare();
	cout << endl;

	//UPCASTING - early binding va afisa metoda din parinte
	a2.metodaSuprascrisa();

	cout << "UPCASTING - late binding\n";
	Autovehicul *a3 = new Autovehicul();
	Motocicleta *m2 = new Motocicleta(true, 3, false, "BMW");

	a3 = m2;
	a3->afisareAutovehicul();
	cout << endl;
	//UPCASTING - late binding va afisa metoda din copil
	a3->metodaSuprascrisa();
}