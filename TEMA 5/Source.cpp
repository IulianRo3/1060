#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class ExceptieCustomSalariu : public exception {
public:
	const char *what() {
		return "O eroare a fost prinsa. Salariul angajatului nu poate fi mai mic de 1500 lei.\n";
	}
};

class Angajat {
protected:
	char *nume;
	string telefon;
	int varsta;
	double salariu;

	const int badgeID;
	static int badgeTemporar;
public:
	Angajat() :badgeID(badgeTemporar) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->telefon = "0000000000000";
		this->varsta = 20;
		this->salariu = 2000;
	}

	Angajat(string telefon, int varsta, double salariu) :badgeID(badgeTemporar) {
		if (telefon.length() >= 10) {
			this->telefon = telefon;
		}
		else {
			throw exception("Nr de telefon trebuie sa aiba minim 10 cifre.");
		}
		if (varsta >= 18 && varsta <= 65) {
			this->varsta = varsta;
		}
		else {
			throw exception("Un angajat poate munci daca are intre 18 si 65 de ani.");
		}
		if (salariu >= 1500) {
			this->salariu = salariu;
		}
		else {
			throw ExceptieCustomSalariu();
		}

		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
	}

	Angajat(const char *nume, int varsta, double salariu, string telefon) :badgeID(badgeTemporar) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);

		this->telefon = telefon;

		this->salariu = salariu;
		this->varsta = varsta;
	}

	Angajat(const Angajat &a) :badgeID(a.badgeID) {
		this->nume = new char[strlen(a.nume) + 1];
		strcpy(this->nume, a.nume);

		this->telefon = a.telefon;

		this->salariu = a.salariu;
		this->varsta = a.varsta;
	}

	//operatori
	Angajat &operator=(const Angajat &a) {
		if (this->nume != NULL) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
		}

		this->telefon = a.telefon;

		this->salariu = a.salariu;
		this->varsta = a.varsta;
		return *this;
	}
	friend ostream &operator<<(ostream &out, Angajat a) {
		out << "Angajat => Nume: " << a.nume << " Telefon: " << a.telefon << " Salariu: " << a.salariu << " Varsta: " << a.varsta
			<< " BadgeID: " << a.badgeID << endl;
		return out;
	}
	friend istream &operator>>(istream &in, Angajat &a) {
		string temp;

		cout << "Nume: "; getline(in, temp);
		if (a.nume != NULL) {
			delete[] a.nume;
		}
		a.nume = new char[temp.length() + 1];
		strcpy(a.nume, temp.c_str());

		cout << "Telefon: "; getline(in, a.telefon);

		cout << "Salariu: ";
		getline(in, temp);
		a.salariu = stod(temp);

		cout << "Varsta: ";
		getline(in, temp);
		a.varsta = stoi(temp);
		return in;
	}
	friend ifstream &operator>>(ifstream &in, Angajat &a) {
		string temp;

		getline(in, temp);
		if (a.nume != NULL) {
			delete[] a.nume;
		}
		a.nume = new char[temp.length() + 1];
		strcpy(a.nume, temp.c_str());

		getline(in, a.telefon);

		getline(in, temp);
		a.salariu = stod(temp);

		getline(in, temp);
		a.varsta = stoi(temp);
		return in;
	}
	friend ofstream &operator<<(ofstream &out, Angajat a) {
		int dimNume = strlen(a.nume) + 1;
		out.write((char*)&dimNume, sizeof(int));

		out.write(a.nume, dimNume);

		int dimTelefon = a.telefon.length() + 1;
		out.write((char*)&dimTelefon, sizeof(int));

		out.write(a.telefon.c_str(), dimTelefon);

		out.write((char*)&a.salariu, sizeof(double));
		out.write((char*)&a.varsta, sizeof(int));

		return out;
	}
	ifstream& citireDinFisBin(ifstream &in) {
		int dimNume = 0;
		in.read((char*)&dimNume, sizeof(int));

		if (this->nume != NULL) {
			delete[] this->nume;
		}
		this->nume = new char[dimNume];
		in.read(this->nume, dimNume);

		int dimTelefon = 0;
		in.read((char*)&dimTelefon, sizeof(int));

		char aux[200];
		in.read(aux, dimTelefon);
		this->telefon = aux;

		in.read((char*)&this->salariu, sizeof(double));
		in.read((char*)&this->varsta, sizeof(int));

		return in;
	}
	void scriereInFisTxt(ofstream &out) {
		out << this->nume << endl << this->telefon << endl << this->salariu << endl << this->varsta << endl << this->badgeID << endl;
	}
	//setteri si getteri
	int getVarsta() {
		return varsta;
	}
	char *getNume() {
		return nume;
	}
	void setVarsta(int varsta) {
		if (varsta >= 18 && varsta <= 65) {
			this->varsta = varsta;
		}
		else {
			throw exception("Un angajat poate munci daca are intre 18 si 65 de ani.");
		}
	}
	void setNume(char *nume) {
		if (nume == NULL) {
			throw exception("Numele introdus este NULL.");
		}
		else {
			if (this->nume != NULL) {
				delete[] this->nume;
			}
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}
	~Angajat() {
		if (this->nume != NULL) {
			delete[] this->nume;
		}
	}
	virtual void marireSalariu() {
		this->salariu += 200;
	}
};
int Angajat::badgeTemporar = 10000;

class Frizer :public Angajat {
private:
	bool esteCunoscut;
	int tarif;
public:
	Frizer() {
		this->esteCunoscut = true;
		this->tarif = 30;
	}
	Frizer(int tarif, bool esteCunoscut, string telefon, int varsta, double salariu) :Angajat(telefon, varsta, salariu) {
		this->tarif = tarif;
		this->esteCunoscut = esteCunoscut;
	}
	Frizer(const Frizer &f) :Angajat(f) {
		this->tarif = f.tarif;
		this->esteCunoscut = f.esteCunoscut;
	}
	Frizer &operator=(const Frizer &f) {
		Angajat::operator=(f);

		this->tarif = f.tarif;
		this->esteCunoscut = f.esteCunoscut;
		return *this;
	}
	void marireSalariu() {
		this->salariu += 500;
	}
	friend ostream &operator<<(ostream &out, Frizer f) {
		out << (Angajat)f;//te folosesti de mostenire

		out << "Frizer => Tarif: " << f.tarif << " EsteCunoscut: " << boolalpha << f.esteCunoscut << endl;
		return out;
	}
	friend istream &operator>>(istream &in, Frizer &f) {
		in >> (Angajat&)f;//te folosesti de mostenire

		string temp;
		cout << "Tarif: ";
		getline(in, temp);
		f.tarif = stoi(temp);
		
		cout << "Este cunoscut: ";
		getline(in, temp);
		f.esteCunoscut = stoi(temp);
		return in;
	}
};

class Ministru :public Angajat {
private:
	bool esteCorupt;
	bool arePensieSpeciala;
public:
	Ministru() {
		this->esteCorupt = true;
		this->arePensieSpeciala = true;
	}
	Ministru(bool esteCorupt, bool arePensieSpeciala, string telefon, int varsta, double salariu) :Angajat(telefon, varsta, salariu) {
		this->esteCorupt = esteCorupt;
		this->arePensieSpeciala = arePensieSpeciala;
	}
	Ministru(const Ministru &m) :Angajat(m) {
		this->esteCorupt = m.esteCorupt;
		this->arePensieSpeciala = m.arePensieSpeciala;
	}
	Ministru &operator=(const Ministru &m) {
		Angajat::operator=(m);

		this->esteCorupt = m.esteCorupt;
		this->arePensieSpeciala = m.arePensieSpeciala;
		return *this;
	}
	void marireSalariu() {
		this->salariu += 7000;
	}
	friend ostream &operator<<(ostream &out, Ministru m) {
		out << (Angajat)m;//te folosesti de mostenire

		out << "Ministru => EsteCorupt: " << boolalpha << m.esteCorupt << " ArePensieSpeciala: " << boolalpha << m.arePensieSpeciala << endl;
		return out;
	}
	friend istream &operator>>(istream &in, Ministru &m) {
		in >> (Angajat&)m;//te folosesti de mostenire

		string temp;
		cout << "Este corupt: ";
		getline(in, temp);
		m.esteCorupt = stoi(temp);

		cout << "Are pensie speciala: ";
		getline(in, temp);
		m.arePensieSpeciala = stoi(temp);
		return in;
	}
};

class ICompanie {
public:
	virtual void adaugaAngajat(Angajat a) = 0;
	virtual void stergeAngajat(int index) = 0;
};

class Companie : public ICompanie {
private:
	string denumire;
	Angajat *listaAngajati;
	int nrAngajati;
public:
	Companie() {
		this->listaAngajati = NULL;
		this->nrAngajati = 0;
		this->denumire = "Companie fantoma";
	}
	Companie(string denumire, Angajat* listaAngajati, int nrAngajati) {
		this->denumire = denumire;
		this->nrAngajati = nrAngajati;

		this->listaAngajati = new Angajat[nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->listaAngajati[i] = listaAngajati[i];
		}
	}
	Companie(const Companie &c) {
		this->denumire = c.denumire;
		this->nrAngajati = c.nrAngajati;

		this->listaAngajati = new Angajat[c.nrAngajati];
		for (int i = 0; i < c.nrAngajati; i++) {
			this->listaAngajati[i] = c.listaAngajati[i];
		}
	}
	Companie &operator=(const Companie &c) {
		this->denumire = c.denumire;
		this->nrAngajati = c.nrAngajati;

		if (this->listaAngajati != NULL) {
			delete[] this->listaAngajati;
		}

		this->listaAngajati = new Angajat[c.nrAngajati];

		for (int i = 0; i < c.nrAngajati; i++) {
			this->listaAngajati[i] = c.listaAngajati[i];
		}
		return *this;
	}
	~Companie() {
		if (this->listaAngajati != NULL) {
			delete[] this->listaAngajati;
		}
	}
	//op
	friend ostream &operator<<(ostream &out, Companie m) {
		out << "Companie => Denumire: " << m.denumire << "\nNr.Angajati: " << m.nrAngajati << endl << "Angajati:\n";
		for (int i = 0; i < m.nrAngajati; i++) {
			out << m.listaAngajati[i];//se apeleaza op<< din Angajat
		}
		return out;
	}
	friend istream &operator>>(istream &in, Companie &m) {
		cout << "Denumire companie: ";
		getline(in, m.denumire);

		string temp;
		cout << "Nr.Angajati: ";
		getline(in, temp);
		m.nrAngajati = stoi(temp);

		if (m.listaAngajati != NULL) {
			delete[] m.listaAngajati;
		}

		m.listaAngajati = new Angajat[m.nrAngajati];
		for (int i = 0; i < m.nrAngajati; i++) {
			in >> m.listaAngajati[i];//se apeleaza op>> din Angajat
		}
		return in;
	}
	Angajat &operator[](int index) {
		if (index >= 0 && index < nrAngajati) {
			return this->listaAngajati[index];
		}
		else {
			throw new exception("Index-ul introdus este gresit.");
		}
	}

	bool operator+(Angajat a) {
		if (this->nrAngajati >= 2) {
			adaugaAngajat(a);
			return true;
		}
		return false;
	}

	//fisiere
	void scriereInFisierTXT() {
		ofstream fisTxtOut("CompanieOut.txt");
		if (fisTxtOut.is_open()) {
			fisTxtOut << this->denumire << endl << this->nrAngajati << endl;

			for (int i = 0; i < this->nrAngajati; i++) {
				this->listaAngajati[i].scriereInFisTxt(fisTxtOut);
			}
			fisTxtOut.close();
		}
	}
	friend ifstream &operator>>(ifstream &in, Companie &m) {
		getline(in, m.denumire);

		string temp;
		getline(in, temp);
		m.nrAngajati = stoi(temp);

		if (m.listaAngajati != NULL) {
			delete[] m.listaAngajati;
		}

		m.listaAngajati = new Angajat[m.nrAngajati];

		for (int i = 0; i < m.nrAngajati; i++) {
			in >> m.listaAngajati[i];
		}
		return in;
	}
	friend ofstream &operator<<(ofstream &out, Companie m) {
		int dimDenumire = m.denumire.length() + 1;
		out.write((char*)&dimDenumire, sizeof(int));

		out.write(m.denumire.c_str(), dimDenumire);

		out.write((char*)&m.nrAngajati, sizeof(int));

		for (int i = 0; i < m.nrAngajati; i++) {
			out << m.listaAngajati[i];// se apeleaza op<< ofstream din Angajat
		}
		return out;
	}
	void citireDinFisierBinar(ifstream &in) {
		int dimDenumire = 0;
		in.read((char*)&dimDenumire, sizeof(int));

		char aux[200];
		in.read(aux, dimDenumire);
		this->denumire = aux;

		in.read((char*)&this->nrAngajati, sizeof(int));

		if (this->listaAngajati != NULL) {
			delete[] this->listaAngajati;
		}

		this->listaAngajati = new Angajat[this->nrAngajati];
		
		for (int i = 0; i < this->nrAngajati; i++) {
			this->listaAngajati[i].citireDinFisBin(in);// se apeleaza metoda citireDinFisBin(ifstream &in) din Angajat
		}
	}
	//metode interfata
	void adaugaAngajat(Angajat a) {
		nrAngajati++;
		Angajat *aux = new Angajat[nrAngajati];
		for (int i = 0; i < nrAngajati - 1; i++) {
			aux[i] = this->listaAngajati[i];
		}
		aux[nrAngajati - 1] = a;
		if (this->listaAngajati != NULL) {
			delete[] this->listaAngajati;
		}
		this->listaAngajati = aux;
	}
	void stergeAngajat(int index) {
		nrAngajati--;
		Angajat *aux = new Angajat[nrAngajati];
		int k = 0;
		for (int i = 0; i < nrAngajati + 1; i++) {
			if (i != index) {
				aux[k++] = this->listaAngajati[i];
			}
		}
		if (this->listaAngajati != NULL) {
			delete[] this->listaAngajati;
		}
		this->listaAngajati = aux;
	}
	string getDenumire() {
		return this->denumire;
	}
	Angajat getAngajat(int index) {
		return this->listaAngajati[index];
	}
	void setDenumire(string denumire) {
		if (denumire.empty()) {
			throw exception("Denumirea companiei este incorecta");
		}
		else {
			this->denumire = denumire;
		}
	}
	void setListaAngajati(Angajat *listaAngajati, int nrAngajati) {
		if (listaAngajati == NULL) {
			throw exception("Lista de angajati trimisa este NULL.");
		}
		else {
			this->nrAngajati = nrAngajati;
			if (this->listaAngajati != NULL) {
				delete[] this->listaAngajati;
			}
			this->listaAngajati = new Angajat[nrAngajati];
			for (int i = 0; i < nrAngajati; i++) {
				this->listaAngajati[i] = listaAngajati[i];
			}
		}
	}
};

template<typename T, typename Z> void afisareTemplate(T t, Z z) {
	cout << "Functie template: T= " << t << "  Z= " << z << endl;
}

int main() {
	cout << "merge" << endl;
	//testare try-catch
	try {
		Angajat a1("0755405454", 25, 3200);
		cout << a1 << endl;

		Angajat a2;
		//cin >> a2;
		cout << a2 << endl;
	}
	catch (ExceptieCustomSalariu e) {
		cout << e.what() << endl;
	}

	//testare metoda template
	Frizer f1(100, true, "43224277932", 33, 4000);
	afisareTemplate(f1.getNume(), f1.getVarsta());
	cout << f1;

	Frizer f2;
	cout << "\ncitire frizer\n\n";
	//	cin >> f2;
	cout << f2;

	Ministru m1(true, true, "2224555554555", 23, 9500);
	cout << m1;
	Ministru m2;
	cout << "\ncitire ministru\n\n";
	//	cin >> m2;
	cout << m2;

	//POLIMORFISM -> Ai nevoie de pointeri pt testarea lui-> faci upcasting cand testezi polimorfismul -> transformi o clasa derivata in una de baza
	//si daca ai metode SUPRASCRISE in clasele derivate atunci pe baza pointerilor va sti in spate compilatorul ce metoda sa apeleze

	//Ex: daca ai un Frizer si il transformi in Angajat.....si dupa apelezi pentru noul obiect creat Angajat metoda marireSalariu() atunci
	//in spate se apeleaza pentru obiectul creat Angajat functia marire salariu() din clasa Frizer.


	cout << endl << "Polimorfism\n";
	//salariile initiale sunt 2000 lei
	Ministru *mp = new Ministru();
	Frizer *mf = new Frizer();

	//testare polimorfism
	Angajat *ma1 = mp;
	ma1->marireSalariu();//practic s-a aplicat metoda marireSalariu pe Angajat *ma1....care de fapt in spate apeleaza metoda din Ministru

	//testare polimorfism
	Angajat *ma2 = mf;
	ma2->marireSalariu();//practic s-a aplicat metoda marireSalariu pe Angajat *ma2....care de fapt in spate apeleaza metoda din Frizer


	cout << *ma1 << endl;//indirectare  
	cout << *ma2 << endl; 


	///op. >> si << clasa Companie
	Companie c1;
	//cin >> c1;
	cout << c1 << endl;

	cout << "testare metode din interfata si op[]" << endl;
	Angajat *listaAngajati = new Angajat[2]{ f1,m1 };
	Companie c2("Rares SRL", listaAngajati, 2);

	Ministru m3(true, true, "1111111111111", 23, 6600);
	Ministru m4(true, true, "2222222222222", 53, 5500);

	//adaugare
	c2.adaugaAngajat(m3);
	c2.adaugaAngajat(m4);

	//op[]
	cout << "Index: " << c2[2];

	//stergere
	c2.stergeAngajat(2);
	cout << c2;

	//op +
	Frizer f3(70, true, "666666666666", 25, 4700);
	cout << "A functionat adaugarea unui nou angajat in companie? Raspuns: " << boolalpha << (c2 + f3) << endl;

	//fisiere
	//c2.scriereInFisierTXT();
	cout << "\n\nCitire din fisier text: " << endl;
	ifstream fisInTxt("CompanieOut.txt");
	ofstream fisOutBin("CompanieOutBin.bin", ios::binary);

	if (fisInTxt.is_open() && fisOutBin.is_open()) {
		//citire din fis txt
		fisInTxt >> c1;
		//afisare in consola
		cout << c1;
		fisInTxt.close();

		//scriere in fisier binar
		fisOutBin << c1;
		fisOutBin.close();
	}

	ifstream fisInBin("CompanieOutBin.bin", ios::binary);
	if (fisInBin.is_open()) {
		//citire din fisier binar
		c1.citireDinFisierBinar(fisInBin);
		cout << "\n\n~~~~~Afisare companie dupa ce s-a scris in fisier binar si citit inapoi:\n\n" << c1;
		fisInBin.close();
	}
}