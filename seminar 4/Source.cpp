#include<iostream>
using namespace std;
class Elev {
private:
	char *CNP;
public:
	char *nume;
	int nrNoteMate;
	int *noteMate;
	int nrNoteRomana;
	int noteRomana[100];
	const int cod;
	static int nrElev;

	Elev() :cod(0) {
		this->CNP = NULL;
		this->noteMate = NULL;
		this->nume = NULL;
	}
	Elev(const char* CNPNou, const char *numeNou) :cod(nrElev) {
		this->CNP = new char[strlen(CNPNou) + 1];
		strcpy(this->CNP, CNPNou);
		this->nume = new char[strlen(numeNou) + 1];
		strcpy(this->nume, numeNou);
		this->noteMate = NULL;
	}
	~Elev() {
		cout << "Destructor" << endl;
		if (this->CNP != NULL) {
			delete[] CNP;
		}
		if (this->nume != NULL) {
			delete[] nume;
		}
		if (this->noteMate != NULL) {
			delete[] noteMate;
		}
	}
	Elev(const char* CNPNou, const char *numeNou, int nrNoteMateNou,
		int *noteMateNou, int nrNoteRomanaNou, int noteRomanaNou[]) :cod() {
		this->CNP = new char[strlen(CNPNou) + 1];
		strcpy(this->CNP, CNPNou);
		this->nume = new char[strlen(numeNou) + 1];
		strcpy(this->nume, numeNou);

		this->nrNoteMate = nrNoteMateNou;
		this->noteMate = new int[nrNoteMateNou];
		for (int i = 0; i < nrNoteMateNou; i++) {
			this->noteMate[i] = noteMateNou[i];
		}
		this->nrNoteRomana = nrNoteRomanaNou;
		for (int i = 0; i < nrNoteRomanaNou; i++) {
			this->noteRomana[i] = noteRomanaNou[i];
		}
	}
	Elev(const Elev &elevNou):cod(elevNou.cod) {
		this->CNP = new char[strlen(elevNou.CNP) + 1];
		strcpy(this->CNP, elevNou.CNP);
		this->nume = new char[strlen(elevNou.nume) + 1];
		strcpy(this->nume, elevNou.nume);

		this->nrNoteMate = elevNou.nrNoteMate;
		this->noteMate = new int[elevNou.nrNoteMate];
		for (int i = 0; i < elevNou.nrNoteMate; i++) {
			this->noteMate[i] = elevNou.noteMate[i];
		}
		this->nrNoteRomana = elevNou.nrNoteRomana;
		for (int i = 0; i < elevNou.nrNoteRomana; i++) {
			this->noteRomana[i] = elevNou.noteRomana[i];
		}
	}

	Elev &operator=(const Elev &elevNou) {
		if (this->CNP != NULL) {
			delete[] this->CNP;
		}
		if (this->nume != NULL) {
			delete[] this->nume;
		}
		if (this->noteMate != NULL) {
			delete[] this->noteMate;
		}
		this->CNP = new char[strlen(elevNou.CNP) + 1];
		strcpy(this->CNP, elevNou.CNP);
		this->nume = new char[strlen(elevNou.nume) + 1];
		strcpy(this->nume, elevNou.nume);

		this->nrNoteMate = elevNou.nrNoteMate;
		this->noteMate = new int[elevNou.nrNoteMate];
		for (int i = 0; i < elevNou.nrNoteMate; i++) {
			this->noteMate[i] = elevNou.noteMate[i];
		}
		this->nrNoteRomana = elevNou.nrNoteRomana;
		for (int i = 0; i < elevNou.nrNoteRomana; i++) {
			this->noteRomana[i] = elevNou.noteRomana[i];
		}
		return *this;
	}

	int getNrNoteMate() {
		return this->nrNoteMate;
	}
	void setNrNoteMate(int nrNoteMateNou) {
		this->nrNoteMate = nrNoteMateNou;
	}
	char* getCNP() {
		return this->CNP;
	}
	void setCNP(const char *CNPNou) {
		if (CNPNou == NULL) {
			throw new exception("CNP-ul este trimis NULL din main()!");
		}
		else
		{
			if (this->CNP != NULL) {
				delete[] CNP;
			}
			this->CNP = new char[strlen(CNPNou) + 1];
			strcpy(this->CNP, CNPNou);
		}
	}
};
int Elev::nrElev = 1000;

int main() {
	cout << "Merge" << endl;
	Elev e1;
	e1.nrElev = 1001;
	Elev e2("19656546565", "Rares");
	cout << e2.nrElev << endl;
	int noteMate[] = { 7,7,10 };
	int nrNoteMate = 3;
	int noteRomana[] = { 5,8,8,10 };
	int nrNoteRomana = 4;
	Elev e3("143354354354", "Mihai",
		nrNoteMate, noteMate, nrNoteRomana, noteRomana);
	cout << e3.nume << endl;
	cout << e3.getCNP() << endl;
	e3.setCNP("212312121");
	cout << e3.getCNP() << endl;

	Elev e4 = e3;
	Elev e5(e3);
	cout << e5.getCNP() << endl;

	Elev e6;
	e3.setCNP("111112121");
	e6 = e3;
	cout << e6.getCNP() << endl;
}