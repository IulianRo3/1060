#include<iostream>
#include<string>

using namespace std;

class DummyClass {
private:
	string denumire;
	string *listaDeDenumiri;
	int nrDenumiri;

public:
	DummyClass() {
		this->denumire = "default";
		this->nrDenumiri = 2;

		//e pointer lista, evident ca trebuie sa alocam memorie
		this->listaDeDenumiri = new string[this->nrDenumiri];
		for (int i = 0; i < this->nrDenumiri; i++) {
			this->listaDeDenumiri[i] = "xxx";
		}
	}

	DummyClass(string denumire, string *listaDeDenumiri, int nrDenumiri) {
		this->denumire = denumire;
		this->nrDenumiri = nrDenumiri;

		this->listaDeDenumiri = new string[nrDenumiri];
		for (int i = 0; i < nrDenumiri; i++) {
			this->listaDeDenumiri[i] = listaDeDenumiri[i];
		}
	}

	DummyClass(DummyClass &obiectNou) {
		this->denumire = obiectNou.denumire;
		this->nrDenumiri = obiectNou.nrDenumiri;

		//practic e ca la un vector dinamic int/float/double nu? 
		this->listaDeDenumiri = new string[obiectNou.nrDenumiri];
		for (int i = 0; i < obiectNou.nrDenumiri; i++) {
			this->listaDeDenumiri[i] = obiectNou.listaDeDenumiri[i];
		}
	}

	~DummyClass() {
		if (this->listaDeDenumiri != NULL) {
			delete[] this->listaDeDenumiri;
		}
	}

	string getDenumire() {
		return this->denumire;
	}

	void setDenumire(string denumireNoua) {
		//facem o validare.....daca string-ul primit este gol, adica ""
		if (denumireNoua.empty()) {
			throw new exception("denumirea nu a fost introdusa");
		}
		this->denumire = denumireNoua;
	}
	string getDenumireDinLista(int index) {
		return this->listaDeDenumiri[index];
	}
	//practic ca la un (int *)
	void setLista(string *lista, int dim) {
		if (lista == NULL) {
			throw new exception("Lista primita este NULL");
		}
		else {
			//dezalocam memoria existenta
			//#memory #leaks
			if (this->listaDeDenumiri != NULL) {
				delete[] this->listaDeDenumiri;
			}

			this->nrDenumiri = dim;//setam noua dimensiune a listei

			//realocam lista
			this->listaDeDenumiri = new string[dim];
			for (int i = 0; i < dim; i++) {
				this->listaDeDenumiri[i] = lista[i];
			}
		}
	}
	//op egal.
	DummyClass &operator=(DummyClass &obiectNou) {
		//dezalocare intai evident
		if (this->listaDeDenumiri != NULL) {
			delete[] this->listaDeDenumiri;
		}

		this->denumire = obiectNou.denumire;
		this->nrDenumiri = obiectNou.nrDenumiri;

		this->listaDeDenumiri = new string[obiectNou.nrDenumiri];
		for (int i = 0; i < obiectNou.nrDenumiri; i++) {
			this->listaDeDenumiri[i] = obiectNou.listaDeDenumiri[i];
		}
		return *this;
	}

	friend ostream &operator<<(ostream &consola, DummyClass d);
};
ostream &operator<<(ostream &consola, DummyClass d) {
	consola << "Denumire: " << d.denumire << " Nr.Denumiri: " << d.nrDenumiri << " \nDenumiri:";
	for (int i = 0; i < d.nrDenumiri; i++) {
		consola << d.listaDeDenumiri[i] << " ";
	}
	consola << endl;
	return consola;
}

int main() {
	DummyClass d1;
	cout << "D1: " << d1;

	string lista1[] = { "vvv1","vvv2", "vvv3" };
	DummyClass d2("Rares", lista1, 3);
	cout << "D2: " << d2;

	string lista2[] = { "elem1","elem2", "elem3", "elem4" };
	DummyClass *d3 = new DummyClass("Masina", lista2, 4);
	cout << "D3: " << *d3;

	string lista3[] = { "aaa1","aaa2", "aaa3", "aaa4" };
	d3->setLista(lista3, 4);
	cout << "D3 modificat: " << *d3;


	cout << endl << endl;
	DummyClass d4;
	d4 = d2;//op egal
	cout << "D4: " << d4;

	DummyClass d5(d2);//constr copiere
	cout << "D5: " << d5;
}