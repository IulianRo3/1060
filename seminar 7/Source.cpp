#include<iostream>
using namespace std;

class Film {
private:
	const int cod;
	char *denumire;
	int nrNote;
	int *note;
public:
	Film() :cod(0) {
		this->denumire = new char[strlen("Film default") + 1];
		strcpy(this->denumire, "Film default");
		this->nrNote = 2;
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++) {
			this->note[i] = 10 - i;
		}
	}
	Film(int cod, const char *denumire, int nrNote, int *note) :cod(cod) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->nrNote = nrNote;
		this->note = new int[nrNote];
		for (int i = 0; i < nrNote; i++) {
			this->note[i] = note[i];
		}
	}
	Film(Film &filmNou) :cod(filmNou.cod) {
		this->denumire = new char[strlen(filmNou.denumire) + 1];
		strcpy(this->denumire, filmNou.denumire);
		this->nrNote = filmNou.nrNote;
		this->note = new int[filmNou.nrNote];
		for (int i = 0; i < filmNou.nrNote; i++) {
			this->note[i] = filmNou.note[i];
		}
	}
	~Film() {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
		if (this->note != NULL) {
			delete[] this->note;
		}
	}
	int getNota(int index) {
		return this->note[index];
	}
	char* getDenumire() {
		return this->denumire;
	}
	void setDenumire(const char* denumire) {
		if (denumire == NULL) {
			throw new exception("Denumire este NULL");
		}
		else {
			if (this->denumire != NULL) {
				delete[] this->denumire;
			}
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
	}
	void setNote(int *note, int nrNote) {
		if (note == NULL) {
			throw new exception("Note este NULL");
		}
		else {
			if (this->note != NULL) {
				delete[] this->note;
			}
			this->nrNote = nrNote;
			this->note = new int[nrNote];
			for (int i = 0; i < nrNote; i++) {
				this->note[i] = note[i];
			}
		}
	}
	//operatori
	Film &operator=(const Film &filmNou) {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
		if (this->note != NULL) {
			delete[] this->note;
		}
		this->denumire = new char[strlen(filmNou.denumire) + 1];
		strcpy(this->denumire, filmNou.denumire);
		this->nrNote = filmNou.nrNote;
		this->note = new int[filmNou.nrNote];
		for (int i = 0; i < filmNou.nrNote; i++) {
			this->note[i] = filmNou.note[i];
		}
		return *this;
	}

	int operator[](int index) {
		if (index >= 0 && index < this->nrNote) {
			return this->note[index];
		}
	}
	bool operator>(Film f) {
		if (this->nrNote > f.nrNote) {
			return true;
		}
		return false;
	}
	friend ostream &operator<<(ostream &consola, Film film);
	friend istream &operator>>(istream &in, Film &film);

};
ostream &operator<<(ostream &consola, Film film) {
	consola << "Cod: " << film.cod << " Denumire: " << film.denumire
		<< " NrNote: " << film.nrNote << " Note: ";
	for (int i = 0; i < film.nrNote; i++) {
		consola << film.note[i] << " ";
	}
	consola << endl;
	return consola;
}
istream &operator>>(istream &in, Film &film) {
	//dezalocare memorie existenta
	delete[] film.denumire;
	delete[] film.note;
	//suprascriere obiect film cu valori citite de la tastatura
	char aux[100];
	cout << "Denumire: "; in >> aux;
	film.denumire = new char[strlen(aux) + 1];
	strcpy(film.denumire, aux);

	cout << "Nr Note: ";  in >> film.nrNote;
	film.note = new int[film.nrNote];
	for (int i = 0; i < film.nrNote; i++) {
		cout << "Nota" << i << " :"; in >> film.note[i];
	}
	return in;
}
int main() {
	cout << "Seminar 7 \n\n";

	Film f1;

	int note1[] = { 9,8 };
	int nrNote1 = 2;

	Film f2(1000, "Avengers", nrNote1, note1);
	f2.setDenumire("Iron Man 1");
	int note2[] = { 9,8,7,7 };
	int nrNote2 = 4;
	f2.setNote(note2, nrNote2);
	cout << "f2: " << f2;
	//constr de copiere
	Film f3 = f2;
	cout << "f3: " << f3;
	//operatori
	Film f4;
	f4 = f2;//op egal
	cout << f4;
	//op >>
	Film f5;
	//cin >> f5;
	cout << f5;

	//op []
	cout << f3[3] << endl;

	//op >
	cout << "f3 este mai mare decat f5? raspuns: " << (f3 > f5) << endl;

	//sa va uitati la grupa 1047 - sem 7 cum am facut op cast (apelare implicita si explicita...)
}