#include<iostream>

using namespace std;

class Contor {
private:
	const int numar;
	char *culoare;
	int *valori;
	int nrValori;
	bool activ;

public:
	Contor() :numar(0) {
		this->culoare = new char[strlen("Anonim") + 1];
		strcpy(this->culoare, "Anonim");
		this->activ = false; //e ok si 0(false) sau 1(true)
		this->nrValori = 2;
		this->valori = new int[this->nrValori];
		for (int i = 0; i < this->nrValori; i++) {
			this->valori[i] = i;
		}
	}
	Contor(int numar, const char* culoare, bool activ,
		int nrValori, int *valori) :numar(numar) {
		this->activ = activ;
		this->nrValori = nrValori;

		if (culoare != NULL) {
			this->culoare = new char[strlen(culoare) + 1];
			strcpy(this->culoare, culoare);
		}
		else
		{
			this->culoare = NULL;
		}
		if (valori != NULL) {
			this->valori = new int[nrValori];
			for (int i = 0; i < nrValori; i++) {
				this->valori[i] = valori[i];
			}
		}
		else
		{
			this->valori = NULL;
		}
	}
	Contor(Contor &contorNou) :numar(contorNou.numar) {
		this->activ = contorNou.activ;
		this->nrValori = contorNou.nrValori;

		this->culoare = new char[strlen(contorNou.culoare) + 1];
		strcpy(this->culoare, contorNou.culoare);
		this->valori = new int[contorNou.nrValori];
		for (int i = 0; i < contorNou.nrValori; i++) {
			this->valori[i] = contorNou.valori[i];
		}
	}
	//////////////////////OPERATORI////////////////////////////
	Contor &operator=(const Contor &contorNou) {
		if (this->culoare != NULL) {
			delete[] this->culoare;
		}
		if (this->valori != NULL) {
			delete[] this->valori;
		}

		this->activ = contorNou.activ;
		this->nrValori = contorNou.nrValori;

		this->culoare = new char[strlen(contorNou.culoare) + 1];
		strcpy(this->culoare, contorNou.culoare);
		this->valori = new int[contorNou.nrValori];
		for (int i = 0; i < contorNou.nrValori; i++) {
			this->valori[i] = contorNou.valori[i];
		}
		return *this;
	}
	Contor &operator++() {
		this->valori[0] += 50;
		return *this;
	}
	Contor operator++(int) {
		Contor temp = *this;
		this->valori[0] += 50;
		return temp;
	}
	Contor &operator+(int valoareMarita) {
		this->valori[0] += valoareMarita;
		return *this;
	}
	friend ostream &operator<<(ostream& consola, Contor c);
	friend istream &operator>>(istream& in, Contor &c);

	~Contor() {
		if (this->culoare != NULL) {
			delete[] this->culoare;
		}
		if (this->valori != NULL) {
			delete[] this->valori;
		}
	}
	void afisareObiect() {
		cout << "Numar: " << this->numar << " ;Culoare: "
			<< this->culoare << " ;Activ: " << this->activ
			<< " ;NrValori: " << this->nrValori << endl;
		cout << "Valori: ";
		for (int i = 0; i < this->nrValori; i++) {
			cout << this->valori[i] << " ";
		}
		cout << endl;
	}
	char *getCuloare() {
		return this->getCuloare();
	}
	int getValoare(int index) {
		if (index >= 0 && index < this->nrValori) {
			return this->valori[index];
		}
	}
	void setCuloare(const char* culoare) {
		if (culoare == NULL) {
			cout << "Culoare primita este NULL." << endl;
			//exit;
			throw new exception("Culoare primita este NULL.");
		}
		else {
			if (this->culoare != NULL) {
				delete[] this->culoare;
			}
			this->culoare = new char[strlen(culoare) + 1];
			strcpy(this->culoare, culoare);
		}
	}
};

ostream &operator<<(ostream& consola, Contor c) {
	consola << "Numar: " << c.numar << " ;Culoare: "
		<< c.culoare << " ;Activ: " << c.activ
		<< " ;NrValori: " << c.nrValori << endl;
	consola << "Valori: ";
	for (int i = 0; i < c.nrValori; i++) {
		cout << c.valori[i] << " ";
	}
	consola << endl;
	return consola;
}
istream &operator>>(istream& in, Contor &c) {
	delete[] c.culoare;
	delete[] c.valori;

	char aux[100];
	cout << "culoare: "; in >> aux;
	c.culoare = new char[strlen(aux) + 1];
	strcpy(c.culoare, aux);

	cout << "activ: "; in >> c.activ;
	cout << "nrValori: "; in >> c.nrValori;

	cout << "introdu valori" << endl;
	c.valori = new int[c.nrValori];
	for (int i = 0; i < c.nrValori; i++) {
		in >> c.valori[i];
	}

	return in;
}

int main() {
	Contor c1;
	int valori1[] = { 5,10,15,20 };
	Contor c2(1001, "GRI", true, 4, valori1);

	c2.afisareObiect();

	char *culoare = NULL;
	Contor c3(1002, culoare, false, 4, valori1);

	delete[] culoare;//var. dinamice = NULL pot fi dezalocate

	Contor c4(c2);//constr. de copiere
	//Contor c4 = c2;//constr. de copiere


	/////////////OPERATORI///////////////
	//op =
	Contor c5;
	c5 = c2;
	c5.setCuloare("MOV");
	c5.afisareObiect();

	//op ++x 
	cout << (++c5).getValoare(0) << endl;
	//op x++
	cout << (c5++).getValoare(0) << endl;
	cout << c5.getValoare(0) << endl;

	//op << si >>
	cout << c5;
	//cin >> c5;
	//cout << c5;

	//op +
	c5 = c2 + 10; //se pierde referinta daca faci asa si de asta ai valori aiurea bagate
	cout << "c5 + 10 = " << c5.getValoare(0) << endl;
	cout << sizeof(int);
	cout << sizeof(short);

	cout << sizeof(long);
	cout << sizeof(double);


}