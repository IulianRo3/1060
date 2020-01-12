//CLASE - STL
//• reprezinta o librarie de clase template standard(standard template library)
//• acopera principalele structuri de date : vector, lista, stiva, coada, tabela de dispersie(hash - table);
//• pot fi utilizate fara alte modificari pentru tipuri fundamentale sau definite de programator.

//STL=Containere + ITERATORI + ALGORITMI

//Containere: 
//• un obiect ce stocheaza alte obiecte si are metode pentru a le accesa;

//TIP CONTAINERE
//• secventiale : 
		//• vector;
		//• list;
		//• deque; 
//• asociative(valoare – cheie) :
		//• set(multime de chei unice, sortate)
		//• multiset(multime de chei, sortate)
		//• map(multime valori - chei unice, sortate)
		//• multimap(multime valori - chei sortate)
//• adaptive :
		//• stack 
		//• queue
		//• priority_queue


//ITERATORI
	//• forma generalizata a pointerilor; 
	//• utilizati pentru a itera prin elementele containerelor
	//• se comporta ca interfata intre containere si algoritmi
	//• iteratori predefiniti :
			//• ostream_iterator; 
			//• istream_iterator;
			//• reverse_iterator; 
			//• insert_iterator;

//ALGORITMI
	//• functii generice independente de tipul containerului; 
	//• utilizate pentru a prelucra elementele containerelor
	//• folosesc iteratori pentru acces la elemente
	//• functii importante : 
		//• copy;
		//• for_each;
		//• sort;
		//• find;
		//• transform

////Mai multe exemple: https://www.sanfoundry.com/cpp-programming-examples-stl/

#include <iostream>
#include <string>

#include <vector> 
#include <list> 
#include <map> 

using namespace std;

//pt containerul vector trebuie sa adaugi #include <vector> 
//pt containerul list trebuie sa adaugi #include <list> 
//pt containerul map trebuie sa adaugi #include <map> 
//la fel si pt alte containere...

class Elev {
public:
	string nume;
	int varsta = 24;
	Elev() {
		nume = "Rares I";
	}
	Elev(string nume, int varsta) {
		this->nume = nume;
		this->varsta = varsta;
	}
	friend ostream& operator<<(ostream &out, Elev e) {
		cout << "Nume: " << e.nume << " Varsta: " << e.varsta << endl;
		return out;
	}
};
void main() {
	///////////////////////////CONTAINERUL VECTOR

	//definire container vector
	vector<int> v;

	//adaugare element de tip "int" in vector:
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	cout << "Afisare vector pe baza index-ului: ";
	for (int i = 0; i < v.size(); i++) {	//v.size() - dimensiunea vectorului
		cout << v[i] << " ";
	}
	cout << endl;

	//stergerea ultimui element din vector
	v.pop_back();
	cout << "Afisare vector dupa stergerea ultimui element: ";
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	//vectorul poate fi parcurs si prin intermediul iteratorului
	//definire iterator vector
	cout << "Afisare vector printr-un iterator: ";
	vector<int>::iterator it; //folosit pt a itera printr-un container
	for (it = v.begin(); it != v.end(); it++) {//v.begin()-inceputul vectorului; v.end()-sfarsitul vectorului
		cout << *it << " ";// Iteratorii sunt o forma generalizata a pointerilor; ....=> trebuie indirectare inainte de afisare(*it) 
	}
	cout << endl;


	v.clear();//v.clear() este functia folosita pt golirea vectorului de valori
	v.push_back(111);
	cout << "Afisare vector dupa stergere completa si adaugarea unui nou element: ";
	for (int i = 0; i < v.size(); i++) {	//v.size() - dimensiunea vectorului
		cout << v[i] << " ";
	}
	cout << endl;

	//Evident in loc de primitive putem folosi obiecte ----> vector<Obiect> vectorObiecte; //asa o sa fie la examen probabil

	//subiect posibil: afisarea sumei totale/maxim/minim/prima aparitie a maximului/nr total de aparitii ale maximului/iterare prin lista de obiecte si afisare a ceva....
	vector<Elev> vectorElevi;
	vectorElevi.push_back(Elev("Mihai", 17));
	vectorElevi.push_back(Elev("Ion", 15));
	vectorElevi.push_back(Elev("Mioara", 12));
	vectorElevi.push_back(Elev("Cristi", 19));

	//FOARTE IMPORTANT atunci cand folositi orice tip de CONTAINER
	//aveti nevoie de constr. copiere si op. egal cand folositi STL ...mai ales cand aveti variabile dinamice in clasa voastra.

	//acum e nevoie doar de op. << pt afisarea unui Elev in consola.
	vector<Elev>::iterator iteratorVectorElevi;
	for (iteratorVectorElevi = vectorElevi.begin(); iteratorVectorElevi != vectorElevi.end(); iteratorVectorElevi++) {
		cout << *iteratorVectorElevi; //pt afisarea atributelor: iteratorVectorElevi->nume sau iteratorVectorElevi->varsta
	}
	cout << endl;








	///////////////////////////CONTAINERUL LIST
	cout << "\n\nCONTAINERUL LIST\n\n";
	int values[] = { 1, 2, 3 };
	list<int> list1, list2(values, values + sizeof(values) / sizeof(int));
	//list1 - lista goala de int-uri, 
	//list2 - contine toate valorile din values; pt list2 se apeleaza constructorul din clasa list care are ca input 2 iteratori care formeaza intervalul [first,last)
	list<int>::iterator iteratorList; //iterator de tip list

	//adauga un element la inceput
	list1.push_front(10);
	//adauga un element la final
	list1.push_back(20);
	list1.push_front(100);
	list1.push_front(100);
	list1.push_back(200);

	//sterge ultimul element din lista
	list2.pop_back();
	//sterge primul element din lista
	list2.pop_front();

	//afisare lista
	cout << "afisare list2 dupa stergere element din fata si spate: ";
	for (iteratorList = list2.begin(); iteratorList != list2.end(); iteratorList++) {
		cout << *iteratorList << " ";
	}
	cout << endl;

	cout << "afisare primul el. din lista 1: " << list1.front() << endl; //-> afiseaza primul element din lista
	cout << "afisare ultimul el. din lista 1: " << list1.back() << endl; //-> afiseaza ultimul element din lista

	cout << "afisare list1: ";
	for (iteratorList = list1.begin(); iteratorList != list1.end(); iteratorList++) {
		cout << *iteratorList << " ";
	}
	cout << endl;

	list1.remove(100);//va sterge toate valorile egale cu 100 din lista 1
	cout << "afisare list1 dupa stergerea nr 100 list lista: ";
	for (iteratorList = list1.begin(); iteratorList != list1.end(); iteratorList++) {
		cout << *iteratorList << " ";
	}
	cout << endl;

	//alte fct:
	//list1.size()-dimensiunea listei
	//list1.unique()-sterge din lista toate valorile duplicate
	//list1.reverse(); -inverseaza lista
	//list1.sort(); -sorteaza lista


	list<Elev> listaElevi;
	listaElevi.push_front(Elev("Rodica", 12));
	listaElevi.push_back(Elev("Marinela", 18));
	listaElevi.push_front(Elev("Andreea", 19));
	list<Elev>::iterator iteratorlistaElevi;

	//afisare nume lista elevi
	//lista se poate afisa doar prin iteratori
	cout << "afisare nume lista elevi: ";
	for (iteratorlistaElevi = listaElevi.begin(); iteratorlistaElevi != listaElevi.end(); iteratorlistaElevi++) {
		cout << iteratorlistaElevi->nume << " ";
	}
	cout << endl;

	

	///////////////////////////CONTAINERUL MAP
	cout << "\n\nCONTAINERUL MAP\n\n";
	map<int, Elev> mapElevi; //map -> se bazeaza pe cheie - valoare....cheia e de tip int si valoarea este un Elev...nu pot exista chei identice..
	map<int, Elev>::iterator itMapElevi;

	Elev e1;
	Elev e2("Marius", 16);
	Elev e3("Alex", 18);
	Elev e4("Viorel", 15);
	Elev e5("Marian", 14);

	//adaugare in map
	mapElevi.insert(pair<int, Elev>(1001, e1)); //prin intermediul unei perechi(pair) se adauga datele in map...practic un map e o colectie de perechi<int,Elev>.
	mapElevi.insert(pair<int, Elev>(554, e2));
	mapElevi.insert(pair<int, Elev>(2201, e3));
	mapElevi.insert(pair<int, Elev>(100, e4));
	mapElevi.insert(pair<int, Elev>(312, e5));

	//dimensiune map
	cout << "dimensiune map: " << mapElevi.size() << endl;

	//se poate itera prin map doar prin iteratori
	//afisare map
	for (itMapElevi = mapElevi.begin(); itMapElevi != mapElevi.end(); itMapElevi++) {
		cout << "Cheie: " << (*itMapElevi).first << " Valoare: " << (*itMapElevi).second << endl; //first contine cheia perechii; second contine valoarea perechii;
	}
	cout << endl;

	//stergerea unei perechi din map
	cout << "stergerea perechii cu cheia 312 din map\n";
	mapElevi.erase(312);
	for (itMapElevi = mapElevi.begin(); itMapElevi != mapElevi.end(); itMapElevi++) {
		cout << "Cheie: " << (*itMapElevi).first << " Valoare: " << (*itMapElevi).second << endl; //first contine cheia perechii; second contine valoarea perechii;
	}
	cout << endl;

	cout << "afiseaza valoarea care are cheia 100: " << mapElevi.find(100)->second;
}