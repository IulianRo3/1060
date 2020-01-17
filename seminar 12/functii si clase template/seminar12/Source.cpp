#include<iostream>
using namespace std;

//functii si clase template

//functie template cu un singur tip generic(class/typename)

//int scadere(int a1, int a2); //echivalent cu ce e mai jos;

template<typename A> A scadere(A a1, A a2) {
	return a1 - a2;
}

template<class T> T adunare(T a1, T a2) {
	return a1 + a2;
}

template<typename W, typename Y> Y inmultire(W w, Y y1, Y y2) {
	return w * y1 * y2;
}

//clase template
template<class T> class List {
private:
	int listSize;
	T *listOfElem;
public:
	List() {
		this->listSize = 0;
		this->listOfElem = NULL;
	}
	int getSize() {
		return this->listSize;
	}
	T getElement(int index) {
		if (index >= 0 && index < listSize) {
			return listOfElem[index];
		}
	}
	bool isEmpty() {
		return (listSize == 0);
	}

	void add(T element) {
		listSize++;
		T *aux = new T[listSize];
		for (int i = 0; i < listSize - 1; i++) {
			aux[i] = listOfElem[i];
		}
		aux[listSize - 1] = element;
		if (this->listOfElem != NULL) {
			delete[] listOfElem;
		}
		listOfElem = aux;
	}

	void remove(int index) {
		listSize--;
		T *aux = new T[listSize];
		int k = 0;
		for (int i = 0; i < listSize + 1; i++) {
			if (i != index) {
				aux[k++] = listOfElem[i];
			}
		}
		if (this->listOfElem != NULL) {
			delete[] listOfElem;
		}
		listOfElem = aux;
	}
};

class Persoana {
public:
	int nr;

	Persoana() {
		this->nr = 0;
	}

	Persoana(int nr) {
		this->nr = nr;
	}

	friend ostream &operator <<(ostream& out, Persoana p) {
		out << "Persoana -> Nr=" << p.nr << endl;
		return out;
	}
};
int main() {
	//functii template
	cout << "\nfunctii template\n";
	int a1 = 10, a2 = 20;
	double d1 = 15.5, d2 = 20.1;

	cout << "Scadere intre int-uri: " << scadere(a1, a2) << endl;
	//cout << "Scadere intre int si double cu eroare: " << scadere(a1, d2) << endl; -eroare
	cout << "Scadere intre int si double: " << scadere<double>(a1, d2) << endl;

	cout << "Adunare intre int-uri: " << adunare(a1, a2) << endl;

	cout << "Inmultire intre int si float,float: " << inmultire(a1, 2.5f, 10.1f) << endl;

	//clase template
	cout << "\nclase template\n";

	List<int> listaInt;
	cout << "Marime lista: " << listaInt.getSize() << endl;
	listaInt.add(100);
	listaInt.add(200);
	listaInt.add(300);
	cout << "Marime lista: " << listaInt.getSize() << endl;
	cout << "Valoare 1 din lista este: " << listaInt.getElement(1) << endl;

	listaInt.remove(1);
	cout << "Dupa stergere valoarea 1 din lista este: "
		<< listaInt.getElement(1) << endl;

	List<Persoana> listaDePersoane;
	Persoana p1(44);
	Persoana p2(14);
	Persoana p3(64);
	Persoana p4(84);
	listaDePersoane.add(p1);
	listaDePersoane.add(p2);
	listaDePersoane.add(p3);
	listaDePersoane.add(p4);
	cout << "Marime lista persoane: " << listaDePersoane.getSize() << endl;
	cout << "Valoarea 3 din lista de persoane este: "
		<< listaDePersoane.getElement(3) << endl;

}