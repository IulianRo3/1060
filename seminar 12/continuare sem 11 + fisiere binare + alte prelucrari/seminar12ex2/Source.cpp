#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class SuntSaracException :public exception {
public:
	const char* what() {
		return "Sunt sarac. Nu-mi permit un cadou mai scump de 500 lei.";
	}
};
class Cadou {
private:
	double pret;
	char *numeDestinatar;
public:
	Cadou() {
		this->pret = 15;
		this->numeDestinatar = new char[strlen("Anonim") + 1];
		strcpy(this->numeDestinatar, "Anonim");
		//throw 212121;
	}
	Cadou(double pret, const char *numeDestinatar) {
		if (pret > 500) {
			throw SuntSaracException();
		}
		if (pret > 10) {
			this->pret = pret;
		}
		else {
			throw "Pretul introdus este mai mic ca 10";
		}
		if (strlen(numeDestinatar) > 3) {
			this->numeDestinatar = new char[strlen(numeDestinatar) + 1];
			strcpy(this->numeDestinatar, numeDestinatar);
		}
		else {
			throw length_error("Lungimea numelui destinatarului este mai mica ca 3");
		}
	}
	Cadou(const Cadou &c) {
		this->pret = c.pret;
		this->numeDestinatar = new char[strlen(c.numeDestinatar) + 1];
		strcpy(this->numeDestinatar, c.numeDestinatar);
	}

	Cadou &operator=(const Cadou &c) {
		this->pret = c.pret;
		if (this->numeDestinatar != NULL) {
			delete[] this->numeDestinatar;
		}
		this->numeDestinatar = new char[strlen(c.numeDestinatar) + 1];
		strcpy(this->numeDestinatar, c.numeDestinatar);
		return *this;
	}

	friend ostream& operator<<(ostream& out, Cadou&c) {
		out << "     Pret:" << c.pret << "\n     Denumire destinatar:" << c.numeDestinatar << endl;
		return out;
	}
	friend ofstream& operator<<(ofstream& out, Cadou &c) {
		//afisam valorile membrilor clasei cate 1 pe linie
		out << c.pret << "\n" << c.numeDestinatar << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Cadou &c) {
		cout << "Introdu pret cadou: ";
		in >> c.pret;
		in.ignore();

		cout << "Introdu numele destinatarului: ";
		char aux[100];
		in.getline(aux, sizeof(aux));

		if (c.numeDestinatar != NULL) {
			delete[] c.numeDestinatar;
		}
		c.numeDestinatar = new char[strlen(aux) + 1];
		strcpy(c.numeDestinatar, aux);

		return in;
	}
	friend ifstream& operator>>(ifstream& in, Cadou &c) {
		///------------------------
		//varianta de mai jos e valabila cand fisierul din care citim e de forma: 
		//200
		//Ionut Popescu

		//daca se citeste din fisier/tastatura cu OPERATORUL ">>"(ex: in>>c.pret) si dupa cu "in.getline(aux, sizeof(aux));" nu va functiona bine citirea
		//...pt ca ramane blocat in buffer un sfarsit de linie ("\n")...pt a evita asta trebuie adaugata un in.ignore() intre comenzi. EXEMPLU:

		/*in >> c.pret;
		char aux[100];
		in.ignore();//neaparat apelati functia pentru ca ramane blocat in buffer sfarsitul de linie "\n"
		in.getline(aux, sizeof(aux));

		if (c.numeDestinatar != NULL) {
			delete[] c.numeDestinatar;
		}
		c.numeDestinatar = new char[strlen(aux) + 1];
		strcpy(c.numeDestinatar, aux);*/
		//-------------------------------------------------------------------------------------------------------------------------
		//o varianta mai simpla ar fi citirea folosind string-uri si getline(in,temp) fara a folosi ">>"
		//ATENTIE metoda getline(in,temp) este din namespace-ul std:: , iar in.getline(aux,sizeof(aux)) este din ifstream....sunt doua lucruri complet dif.
		//200
		//Ionut Popescu
		string temp;

		getline(in, temp);//daca fiecare linie va fi citita intr-un string ==> trebuie facute cast-uri din string spre primitiva de care avem nevoie.
		c.pret = stoi(temp);//stoi - cast string->int .....=string to int....nu trebuie invatata pe de rost functia. Este ceva sugestiv..

		//stod - cast string->double
		//stof - cast string->float
		//stol - cast string->long
		//stoi - cast string->bool

		getline(in, temp);//citire linie noua

		if (c.numeDestinatar != NULL) {
			delete[] c.numeDestinatar;//eliberare memorie existenta - asa evitam memory leaks
		}
		c.numeDestinatar = new char[temp.length() + 1];//alocare memorie noua
		strcpy(c.numeDestinatar, temp.c_str());//cast string->char*

		return in;
	}

	///citire si scriere in fis. binare
	void scriereInFisierBinar(ofstream &out) {
		//scriu pretul - functia write are ca input un const char* si dimensiunea in bytes a obiectului salvat
		//astfel toate variabilele salvate trebuie sa fie transformate in char* prin cast: (char*)&variabila
		out.write((char*)&pret, sizeof(double));

		//pentru string/char* - trebuie scrisa intai dimensiunea numelui si dupa numele efectiv..ca sa stiu dupa cati bytes sa citesc.
		int dimNume = strlen(numeDestinatar) + 1;//pt "\0"
		out.write((char*)&dimNume, sizeof(int));

		out.write(numeDestinatar, dimNume);

		//un mod de a intelege ce s-a intamplat mai sus este:
		//se scrie pretul: 200
		//se scrie lungimea variabilei char*: 14 (se aduna si "\0")	 
		//se scrie numele destinatarului: Ionut Popescu
	}

	void citireDinFisierBinar(ifstream &in) {
		in.read((char*)&pret, sizeof(double));

		int dimNume = 0;
		in.read((char*)&dimNume, sizeof(int));

		//aici trb dezalocare pt a evita memory leaks si realocarea memoriei
		if (numeDestinatar != NULL) {
			delete[] numeDestinatar;
		}

		numeDestinatar = new char[dimNume];

		in.read(numeDestinatar, dimNume);
	}
};

class PregatiriDeCraciun {
private:
	string numeMelodie;
	int nrCadouri;
	Cadou *listaCadouri;
public:
	PregatiriDeCraciun() {
		this->numeMelodie = "All I want for Christmas is You.";
		this->nrCadouri = 0;
		this->listaCadouri = NULL;
	}
	PregatiriDeCraciun(string numeMelodie, int nrCadouri, Cadou *listaCadouri) {
		this->numeMelodie = numeMelodie;
		this->nrCadouri = nrCadouri;
		this->listaCadouri = new Cadou[nrCadouri];
		for (int i = 0; i < nrCadouri; i++) {
			this->listaCadouri[i] = listaCadouri[i];
		}
	}
	PregatiriDeCraciun(const PregatiriDeCraciun &p) {
		this->numeMelodie = p.numeMelodie;
		this->nrCadouri = p.nrCadouri;
		this->listaCadouri = new Cadou[p.nrCadouri];
		for (int i = 0; i < p.nrCadouri; i++) {
			this->listaCadouri[i] = p.listaCadouri[i];
		}
	}
	PregatiriDeCraciun operator=(const PregatiriDeCraciun &p) {
		this->numeMelodie = p.numeMelodie;
		this->nrCadouri = p.nrCadouri;
		if (this->listaCadouri != NULL) {
			delete[] this->listaCadouri;
		}
		this->listaCadouri = new Cadou[p.nrCadouri];
		for (int i = 0; i < p.nrCadouri; i++) {
			this->listaCadouri[i] = p.listaCadouri[i];
		}
		return *this;
	}
	~PregatiriDeCraciun() {
		if (this->listaCadouri != NULL) {
			delete[] this->listaCadouri;
		}
	}

	//adaugare/stergere din lista
	void adaugareCadou(Cadou c) {
		this->nrCadouri++;
		Cadou *aux = new Cadou[this->nrCadouri];
		for (int i = 0; i < this->nrCadouri - 1; i++) {
			aux[i] = this->listaCadouri[i];
		}
		aux[nrCadouri - 1] = c;
		if (this->listaCadouri != NULL) {
			delete[] this->listaCadouri;
		}
		this->listaCadouri = aux;
	}
	void stergereCadou(int index) {
		this->nrCadouri--;
		int k = 0;
		Cadou *aux = new Cadou[this->nrCadouri];
		for (int i = 0; i < this->nrCadouri + 1; i++) {
			if (i != index) {
				aux[k++] = this->listaCadouri[i];
			}
		}
		if (this->listaCadouri != NULL) {
			delete[] this->listaCadouri;
		}
		this->listaCadouri = aux;
	}
	friend ostream &operator<<(ostream &out, PregatiriDeCraciun p) {
		out << "Nume melodie: " << p.numeMelodie << "\n";
		out << "Nr.Cadouri: " << p.nrCadouri << "\n";
		out << "Cadouri:\n";
		for (int i = 0; i < p.nrCadouri; i++) {
			out << p.listaCadouri[i] << "\n";
		}
		cout << endl;
		return out;
	}

	friend ofstream &operator<<(ofstream &out, PregatiriDeCraciun p) {
		out << p.numeMelodie << "\n";
		out << p.nrCadouri << "\n";
		for (int i = 0; i < p.nrCadouri; i++) {
			out << p.listaCadouri[i] << "\n";
		}
		cout << endl;
		return out;
	}
	friend ifstream &operator>>(ifstream &in, PregatiriDeCraciun &p) {
		getline(in, p.numeMelodie);

		string temp;
		getline(in, temp);
		p.nrCadouri = stoi(temp);

		//eliberare memorie
		if (p.listaCadouri != NULL) {
			delete[] p.listaCadouri;//memory leaks
		}

		p.listaCadouri = new Cadou[p.nrCadouri];
		for (int i = 0; i < p.nrCadouri; i++) {
			in >> p.listaCadouri[i];
		}
		return in;
	}
	void scriereInFisierBinar(ofstream &out) {
		//cand ai string-uri/char* trebuie sa scrii in fisier si dimensiunea stringului
		//sunt aceeasi pasi ca la char*..ca in clasa Cadou

		int dimensiuneNumeMelodie = numeMelodie.size() + 1;//+1 pentru "\0"
		out.write((char*)&dimensiuneNumeMelodie, sizeof(int));

		//c_str()-functie ce transforma string in char* (asta trebuie trimis ca input)
		out.write(numeMelodie.c_str(), dimensiuneNumeMelodie);

		out.write((char*)&nrCadouri, sizeof(nrCadouri));

		for (int i = 0; i < nrCadouri; i++) {
			listaCadouri[i].scriereInFisierBinar(out);
		}
	}
	void citireDinFisierBinar(ifstream &in) {
		//citirea dimensiunii melodiei
		int dimensiuneNumeMelodie = 0;
		in.read((char*)&dimensiuneNumeMelodie, sizeof(int));//contine deja de la scriere +1 pentru "\0"

		//Poti face citirea unui sir de caractere in 2 feluri:
		
			// -----I---(char*)

		//citim intr-un char* aux sirul de caractere nume melodie si-l asignam variabilei string 
		//char *aux = new char[dimensiuneNumeMelodie];
		//in.read(aux, dimensiuneNumeMelodie);
		//numeMelodie = aux;
		//delete[] aux;


			 // -----II---(char[])

		char aux[200];
		in.read(aux, dimensiuneNumeMelodie);//citim in aux "dimensiuneNumeMelodie" bytes
		numeMelodie = aux;
		//avantaj? nu mai trebuie sa dezaloci memoria temporara folosita char*


		in.read((char*)&nrCadouri, sizeof(int));

		if (listaCadouri != NULL) {
			delete[] listaCadouri;
		}
		listaCadouri = new Cadou[nrCadouri]; //evitare memoryleak si realocare

		for (int i = 0; i < nrCadouri; i++) {
			listaCadouri[i].citireDinFisierBinar(in);
		}
	}
};
void main() {
	try {
		Cadou c1;
		Cadou c2;
	}
	catch (int i) {
		cerr << "A fost prinsa o exceptie: " << i << endl;
	}

	try {
		//Cadou c1(6, "Ionut"); //->valabil pt throw-ul nr 2
		//Cadou c2(100, "Ion"); //->valabil pt throw-ul nr 3
		Cadou c3(700, "Rares"); //->valabil pt throw-ul nr 1
	}
	catch (const char* e) {
		cerr << "A fost prinsa o exceptie: " << e << endl;
	}
	catch (length_error e) {
		cerr << e.what() << endl;
	}
	catch (SuntSaracException e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "A fost prinsa o exceptie prin catch-ul default" << endl;
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

	cout << "\n\nCitire si scriere in fisiere text. \n";
	try {
		ofstream fisTextOut("fisTextOut.txt");
		if (fisTextOut.is_open()) {
			Cadou c3(200, "Maria Ioana");

			fisTextOut << c3;

			fisTextOut.close();
		}
		else {
			throw "LA SCRIEREA IN FISIER -> Fisierul nu a fost deschis corect.\n";
		}
	}
	catch (const char* e) {
		cerr << e << endl;
	}

	try {
		ifstream fisTextIn("fisTextOut.txt");
		if (fisTextIn.is_open()) {
			Cadou c1;
			fisTextIn >> c1;
			cout << c1;
			fisTextIn.close();
		}
		else {
			throw "LA CITIREA DIN FISIER -> Fisierul nu a fost deschis corect.\n";
		}
	}
	catch (const char* e) {
		cerr << e << endl;
	}

	//fstream fisTxt("fisTextOut.txt", ios::in | ios::out);//se comporta ca si ofstream si ifstream in acelasi timp
	//fisTxt << "sasas";
	//int x;
	//fisTxt >> x;


	Cadou c5(160.5, "Maria");
	Cadou c7(350, "Mihaela");
	Cadou c8(500, "Radu");
	Cadou c9(400, "Rares");

	Cadou *listaCadouri = new Cadou[3]{ c5, c7, c8 };
	PregatiriDeCraciun p1;
	PregatiriDeCraciun p2("Afara ninge linistit", 3, listaCadouri);
	//adaugare/stergere cadou
	cout << "adaugare/stergere cadou" << endl;
	p2.adaugareCadou(c9);
	cout << "adaugare\n" << p2 << endl;
	p2.stergereCadou(3);
	cout << "stergere\n" << p2 << endl;

	ofstream outBinary("cadouBinOut.bin", ios::out | ios::binary);
	if (outBinary.is_open()) {
		c7.scriereInFisierBinar(outBinary);
		outBinary.close();
	}
	else {
		cout << "cadouBinOut.bin nu a putut fi deschis.\n";
		return;
	}

	ofstream outBinaryPregatiri("pregatiriDeCraciunBinOut.bin", ios::out | ios::binary);
	if (outBinaryPregatiri.is_open()) {
		p2.scriereInFisierBinar(outBinaryPregatiri);
		cout << "p2 a fost scris in fisierul binar.\n";
		outBinaryPregatiri.close();
	}
	cout << "\n\nCitire si afisare din fisier binar: \n";
	ifstream inBinaryPregatiri("pregatiriDeCraciunBinOut.bin", ios::in | ios::binary);
	if (inBinaryPregatiri.is_open()) {
		p2.citireDinFisierBinar(inBinaryPregatiri);
		cout << "\n\np2 citit din fisierul binar: \n" << p2 << endl;
		inBinaryPregatiri.close();
	}
}