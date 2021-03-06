#include<iostream>
#include<string> //includeti pentru string libraria string

using namespace std;

class Magazin {
private:
	char *numeMagazin;
	unsigned int nrProduse;
	int *preturiProduse;
	bool esteNonStop;
	string culoareMagazin;//asa se defineste un string
public:
	Magazin() {
		this->numeMagazin = new char[strlen("Magazin default") + 1];
		strcpy(this->numeMagazin, "Magazin default");
		this->esteNonStop = false;

		this->culoareMagazin = "Negru"; //usor nu? :)) 

		this->nrProduse = 2;
		this->preturiProduse = new int[nrProduse];
		for (int i = 0; i < nrProduse; i++) {
			this->preturiProduse[i] = 10 + i;
		}
	}
	Magazin(const char* numeMagazin, unsigned int nrProduse, int *preturiProduse, bool esteNonStop, string culoareMagazin) {

		this->culoareMagazin = culoareMagazin;//la string practic nu mai trebuie sa faci nimic.  atribui direct 

		this->esteNonStop = esteNonStop;
		this->numeMagazin = new char[strlen(numeMagazin) + 1];
		strcpy(this->numeMagazin, numeMagazin);
		this->nrProduse = nrProduse;

		this->preturiProduse = new int[nrProduse];
		for (int i = 0; i < nrProduse; i++) {
			this->preturiProduse[i] = preturiProduse[i];
		}
	}
	Magazin(const Magazin &magazinNou) {
		this->culoareMagazin = magazinNou.culoareMagazin;//string...atribuire directa..practic se comporata ca o primitiva int, float, double

		this->esteNonStop = magazinNou.esteNonStop;
		this->numeMagazin = new char[strlen(magazinNou.numeMagazin) + 1];
		strcpy(this->numeMagazin, magazinNou.numeMagazin);
		this->nrProduse = magazinNou.nrProduse;

		this->preturiProduse = new int[magazinNou.nrProduse];
		for (int i = 0; i < magazinNou.nrProduse; i++) {
			this->preturiProduse[i] = magazinNou.preturiProduse[i];
		}
	}
	~Magazin() {
		if (numeMagazin != NULL) {
			delete[] this->numeMagazin;
		}
		if (preturiProduse != NULL) {
			delete[] this->preturiProduse;
		}
	}
	// get string
	string getCuloareMagazin() {
		return this->culoareMagazin;
	}
	//set string
	void setCuloareMagazin(string culoareMagazin) {
		//validare daca string-ul primit este gol, adica daca vine din main: ""; primitiva ,string nu poate fi NULL;
		if (culoareMagazin.empty()) {
			throw new exception("Culoarea magazinului nu este transmisa");
		}
		this->culoareMagazin = culoareMagazin;//atribuire
	}
	int getPret(int index) {
		if (index >= 0 && index < this->nrProduse) {
			return this->preturiProduse[index];
		}
	}
	char *getNumeMagazin() {
		return this->numeMagazin;
	}
	void setNumeMagazin(const char* numeMagazin) {
		if (numeMagazin == NULL) {
			throw new exception("Numele magazinului este NULL.");
		}
		else {
			if (numeMagazin != NULL) {
				delete[] this->numeMagazin;
			}
			this->numeMagazin = new char[strlen(numeMagazin) + 1];
			strcpy(this->numeMagazin, numeMagazin);
		}
	}

	//operatori
	Magazin &operator=(const Magazin &magazinNou) {
		if (numeMagazin != NULL) {
			delete[] this->numeMagazin;
		}
		if (preturiProduse != NULL) {
			delete[] this->preturiProduse;
		}

		this->esteNonStop = magazinNou.esteNonStop;
		this->numeMagazin = new char[strlen(magazinNou.numeMagazin) + 1];
		strcpy(this->numeMagazin, magazinNou.numeMagazin);
		this->nrProduse = magazinNou.nrProduse;

		this->culoareMagazin = magazinNou.culoareMagazin;//atribuire string

		this->preturiProduse = new int[magazinNou.nrProduse];
		for (int i = 0; i < magazinNou.nrProduse; i++) {
			this->preturiProduse[i] = magazinNou.preturiProduse[i];
		}

		return *this;
	}
	//se poate implementa la fel si pt op. ++
	Magazin &operator--() {
		this->preturiProduse[0] -= 10;
		return *this;
	}
	Magazin operator--(int) {
		Magazin temp = *this;
		this->preturiProduse[0] -= 10;
		return temp;
	}
	//acest operator va returna o valoare din vectorul clasei preturiProduse....
	//adica poti face apelare directa obj[5]->care va intoarce al 5 lea element din vectorul preturiProduse
	int operator[](int index) {
		if (index >= 0 && index < this->nrProduse) {
			return this->preturiProduse[index];
		}
	}

	//se poate implementa la fel si pt op. -= sau *= 
	Magazin &operator+=(int valoare) {
		this->preturiProduse[0] += valoare;
		return *this;
	}
	//se compara obiectul curent cu unul dat.
	//se poate implementa la fel si pt op. < sau op. >= sau op. <= sau op. == sau op !=
	bool operator>(Magazin m) {
		if (this->nrProduse > m.nrProduse) {
			return true;
		}
		return false;
	}
	//op. ! sau  op. negatie
	//daca supraincarcam op ! atunci putem accesa direct membrul privat esteNonStop. Ex de implementare: if(!obj) => adica magazinul NU este non-stop.
	bool operator!() {
		return !this->esteNonStop;
	}
	//operatorul functie () - cand apelam obj("o denumire") -> se va schimba denumirea magazinului. Eliberam memoria inainte.
	Magazin &operator()(const char *numeMagazin) {
		delete[] this->numeMagazin;

		this->numeMagazin = new char[strlen(numeMagazin) + 1];
		strcpy(this->numeMagazin, numeMagazin);
		return *this;
	}
	//operator cast pt tipul unsigned int
	//Exemplu: unsigned int nrProduse = obj; -> practic se face automat cast si variabila din main() nrProduse va primi din obj valoarea membrului privat nrProduse.
	//adica unsigned int nrProduse = obj.nrProduse;(asta se intampla in spate)

	//nu este nevoie sa specificati ce va returna operatorul
	//numele castului reprezinta tipul returnat(adica unsigned int in cazul de fata);
	operator unsigned int() {
		return this->nrProduse;
	}
	//op cast pentru tipul bool
	operator bool() {
		return this->esteNonStop;
	}


	//Se adauga friend in fata unei functii pentru ca trebuie sa accesam membrii privati ai obiectului Magazin din exteriorul clasei.

	//se poate implementa la fel si pt op. - sau op. * sau op. /
	friend Magazin operator+(Magazin m, int valoare); // o adunare poate fi: obj + 4 sau 4 + obj => trebuie implementat operatorul + in 2 forme
	friend Magazin operator+(int valoare, Magazin m);
	//operator de afisare
	friend ostream &operator<<(ostream &consola, const Magazin m);
	//operator de citire de la tastatura
	friend istream &operator>>(istream &in, Magazin &m);

};

ostream &operator<<(ostream &consola, const Magazin m) {
	//am adaugat string-ul la afisare
	consola << "Nume magazin: " << m.numeMagazin << " Este magazin non-stop: " << m.esteNonStop << " Culoare magazin: " << m.culoareMagazin
		<< " Magazinul are " << m.nrProduse << " produse.\n";
	consola << "Preturi produse magazin: ";
	for (int i = 0; i < m.nrProduse; i++) {
		consola << m.preturiProduse[i] << " ";
	}
	consola << endl;
	return consola;
}
istream &operator>>(istream &in, Magazin &m) {
	//dezalocare memorie existenta
	delete[] m.numeMagazin;
	delete[] m.preturiProduse;

	cout << "Citire informatii despre magazin de la tastatura\n"; \

		//am folosit getline pentru a citi mai multe cuvinte cu spatii. Daca citim  "Ana are mere" o sa preia toata valoarea;
		//daca folosim in>>m.culoareMagazin atunci va citit doar primul cuvant adica "Ana";
		//string-ul citit de la tastatura trebuie transformat in char*
		string aux;
	cout << "Nume magazin: "; getline(in, aux);
	m.numeMagazin = new char[aux.length() + 1];//calculeaza dim string-ului...
	strcpy(m.numeMagazin, aux.c_str());

	//citire direct in string
	cout << "Culoare magazin: ";  getline(in, m.culoareMagazin);

	cout << "Este non-stop: "; in >> m.esteNonStop;
	cout << "Nr. produse: "; in >> m.nrProduse;

	cout << "Citire preturi produse: \n";
	m.preturiProduse = new int[m.nrProduse];
	for (int i = 0; i < m.nrProduse; i++) {
		in >> m.preturiProduse[i];
	}
	return in;
}
//op + nu ar trebui sa modifice operandul din stanga/dreapta
//se returneaza un obiect temporar
Magazin operator+(Magazin m, int valoare) {
	Magazin temp = m;//se creaza un obiect nou temporar prin apelarea constr. de copiere
	temp.preturiProduse[0] += valoare;
	return temp;
}
Magazin operator+(int valoare, Magazin m) {
	return m + valoare; //Daca operatorul de mai sus exista puteti sa-l apelati direct. Altfel, luati copy-paste ce se afla mai sus.
}
int main() {
	Magazin m1;

	int preturiProduse[] = { 100,150,170,200 };
	unsigned nrProduse = 4;
	Magazin m2("MegaImage", nrProduse, preturiProduse, true, "Verde");
	cout << m2;

	////////////STRING//////
	m2.setCuloareMagazin("ALBASTRU");//testare setter pt un string
	cout << m2;
	///ca fapt divers va puteti juca usor cu string-urile
	string x = "Rares";
	string y = "Ciobanu";
	x = x + " " + y;//asa se concateneaza string-urile
	cout << endl << endl;


	cout << "Concatenare string-uri: " << x << endl;//va afisa Ciobanu Rares;
	//string-ul are diferite functii. De ex poti afla usor ce lungime are. La char nu poti. 
	cout << "Lungime x: " << x.length() << endl;
	//puteti afla usor orice caracter in string. se comporata ca un vector de litere
	cout << "Primul caracter din string este: " << x[0] << endl;
	//sau puteti modifica orice caracter din string
	x[0] = 'M';
	cout << "String-ul modificat: " << x << endl << endl;
	//citirea unui string de la tastatura: cin>>x;


	//const de copiere
	Magazin m3 = m2;
	m3.setNumeMagazin("Metro");
	cout << m3 << "//////////////////////////Operatori///////////////////////" << endl << endl;

	//op =
	Magazin m4;
	m4 = m2;
	cout << m4;

	//op >> si <<
	Magazin m5;
	//cin >> m5;
	cout << m5 << endl;

	cout << "Operator --" << endl;

	//operator -- pre-decrementat
	cout << "\n\n\nOperator -- " << endl << m4.getPret(0) << endl;
	cout << (--m4).getPret(0) << endl;

	//operator -- post-decrementat
	cout << (m4--).getPret(0) << endl;
	cout << m4.getPret(0) << endl;

	//operator []
	cout << "\n\nOperator []: " << m4[2] << endl << endl;

	cout << "Operator + (obj + int)" << endl;
	//op + pt cazul obiect + int
	m4 = m4 + 10;
	cout << m4 << endl;

	cout << "Operator + (int + obj)" << endl;
	//op + pt cazul int + obiect
	m4 = 20 + m4;
	cout << m4 << endl;

	//op +=
	cout << "Operator +=" << endl;
	m4 += 100;
	cout << m4 << endl;

	//op >
	cout << "Operator >" << endl;
	if (m4 > m5) {
		cout << "m4 are mai multe produse in magazin decat m5" << endl;
	}
	else {
		cout << "m5 are mai multe produse in magazin decat m4" << endl;
	}
	cout << endl;
	//op !
	//m5.esteNonStop = false => !m5 va nega false => true si fa intra in blocul if
	cout << "Operator !" << endl;
	if (!m5) {
		cout << "Magazinul NU este deschis non-stop\n" << endl;
	}

	//op ()
	cout << "Operator ()" << endl;
	cout << m5("Magazin Cu Alt Nume") << endl;

	//operator cast pt bool si unsigned int
	cout << "Operator cast" << endl;
	bool esteNonStop = m5;
	unsigned int nrProduseDinMagazin = m5;
	//double nrProduseDinMagazin11 = m5; //asta nu va merge pentru ca nu este incarcat operatorul cast pt double
	cout << esteNonStop << " " << nrProduseDinMagazin << endl;
}