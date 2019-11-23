#include<iostream>
#include<string>
using namespace std;

class Animal {
private:
	int varsta;
protected:
	string nume;
public:
	double greutate;

	Animal(string nume, double greutate) {
		this->nume = nume;
		this->greutate = greutate;

		this->varsta = 5;
	}

	int getVarsta() {
		return this->varsta;
	}

	void afisareAnimal() {
		cout << "Nume: " << this->nume << " Greutate: " <<
			this->greutate << " Varsta: " <<
			this->varsta << endl;
	}
};
//Pisica = toti membrii/fct Animal + int vieti;
class Pisica : public Animal {
public:
	int vieti;
	Pisica(int vieti) :Animal("Tom", 3.5) {
		this->vieti = vieti;
	}
	Pisica(string nume, double greutate, int vieti)
		:Animal(nume, greutate) {
		this->vieti = vieti;
	}

	void afisarePisica() {
		cout << "Pisica ";
		afisareAnimal();
		cout << " Vieti: " << this->vieti << endl;
	}
};

class Caine: private Animal {
public:
	Caine() :Animal("Tom", 3.5) {

	}
};

class Vaca {

};

int main() {
	Animal a1("Animal 1", 5.4);
	a1.afisareAnimal();

	Pisica p1(9);
	p1.afisarePisica();


	Pisica p2("Wiskas", 3.4, 8);
	p2.afisarePisica();

	Caine c;
	//c.getVarsta(); -> eroare de compilare....
	//pentru ca modificatorul de access de la mostenirea clasei caine din animal este private 
}