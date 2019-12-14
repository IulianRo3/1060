#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class SuntSaracException : public exception {
public:
	const char* what() {
		return "Sunt sarac. Nu-mi permit un cadou mai scump de 500 lei.\n";
	}
};
class Cadou {
private:
	double pret; //pretul nu poate fi mai mic decat 10
	char *numeDestinatar; //dimensiunea numelui trebuie sa fie mai mare ca 3
public:
	Cadou() {
		this->pret = 20;
		this->numeDestinatar = new char[strlen("Anonim") + 1];
		strcpy(this->numeDestinatar, "Anonim");
		//throw 12121;
	}
	Cadou(double pret, const char *numeDestinatar) {
		if (pret > 500) {
			throw SuntSaracException();
		}
		if (pret > 10) {
			this->pret = pret;
		}
		else {
			throw "Pretul introdus este mai mic decat 10\n";
		}
		if (strlen(numeDestinatar) > 3) {
			this->numeDestinatar = new char[strlen(numeDestinatar) + 1];
			strcpy(this->numeDestinatar, numeDestinatar);
		}
		else {
			throw length_error("Lungimea numelui destinatarului este mai mica ca 3\n");
		}
	}
	double getPret() {
		return this->pret;
	}
	char *getNumeDestinatar() {
		return this->numeDestinatar;
	}

	friend ostream& operator<<(ostream &out, Cadou &c) {
		out << "Pret cadou: " << c.pret << " Nume Destinatar: "
			<< c.numeDestinatar << endl;
		return out;
	}
	friend ofstream& operator<<(ofstream &out, Cadou &c) {
		out << c.pret << endl << c.numeDestinatar << endl;;
		return out;
	}
	friend istream& operator>>(istream &in, Cadou &c) {
		cout << "Introdu pret cadou: ";
		in >> c.pret;


		cout << "Introdu numele destinatarului";
		char aux[100];
		in.getline(aux, 100);

		delete[] c.numeDestinatar;
		c.numeDestinatar = new char[strlen(aux) + 1];
		strcpy(c.numeDestinatar, aux);

		return in;
	}
	friend ifstream& operator>>(ifstream &in, Cadou &c) {
		in >> c.pret;

		char aux[100];
		in >> aux;

		delete[] c.numeDestinatar;
		c.numeDestinatar = new char[strlen(aux) + 1];
		strcpy(c.numeDestinatar, aux);

		return in;
	}
	void fct() {

	}
};
void main() {
	try {
		Cadou c1;
	}
	catch (int i) {
		cerr << " A fost prinsa o eroare de tip int: " << i << endl;
	}

	try {
		//Cadou c2(5.5, "Mihai");// ->pt al 2 lea throw
		//Cadou c3(65, "Ion");// -> pt al 3 lea throw (length_error)
		Cadou c4(600, "Rares");
	}
	catch (const char* e) {
		cerr << e << endl;
	}
	catch (length_error e) {
		cerr << e.what() << "\n";
		return;
	}
	catch (SuntSaracException e) {
		cerr << e.what() << "\n";
	}
	catch (...) {//catch default
		cerr << "A fost prinsa o eroare in catch-ul default\n";
	}

	//fisiere
	//flag-uri
	//ios::out - ce face
	//ios::app - adauga informatii la un fisier existent
	//ios::nocreate - deschide fisierul daca exista deja.
	//ios::in - pt citire dintr un fisier
	//ios::out - scriere intr-un fisier
	//ios::truc - sterge tot din fisier inainte sa scrii in el 
	//ios::noreplace - doar pt a crea un nou fisier
	//ios::ate - deschide fisierul si merge la sfarsitul lui - fol pt adaugare info la final
	//ios::binary - fisierul deschis va contine doar informatii binare
	cout << "Fisiere: ";

	Cadou c2(125, "Marius");
	cout << c2;

	//scriere in fisier
	ofstream fisTxtOut("fixTxtOut.txt", ios::out);
	if (fisTxtOut.is_open()) {
		fisTxtOut << c2 << endl;
		fisTxtOut.close();
	}
	else {
		throw "Nu s a putut deschide fisierul din dif motive";
	}
	ifstream fisTxtIn("fixTxtOut.txt", ios::in);
	if (fisTxtIn.is_open()) {
		Cadou c6;
		cout << "Citire din fisier\n\n";
		fisTxtIn >> c6;

		cout << c6;
		fisTxtIn.close();
	}
	else {
		throw "Nu s a putut deschide fisierul din dif motive";
	}

}