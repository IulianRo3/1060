#include<iostream>
#include<string>

using namespace std;

class A {
public:
	string nume;

	A() {
		nume = "Ion";
	}
	string getNume() {
		return this->nume;
	}
};

class B :public virtual A {

};

class C :virtual public A {

};

class D : public B, protected C {

};

namespace XYZ {
	int aaa;
	int bbb;
	class Persoana {
		int varsta;
		Persoana() {
			this->varsta = 30;
		}
	};
	int suma(int a, int b) {
		return a + b;
	}
}
//o modalitate de adaugare a unei noi variabile in namespace-ul XYZ
namespace XYZ {
	string nume;
}

namespace aliasXYZ = XYZ;

int main() {
	//mostenire virtuala
	A a;
	B b;
	C c;
	D d;
	cout << "copilul D: Nume:" << d.nume << endl;

	//namespace
	XYZ::aaa = 100;
	cout << "XYZ::aaa=" << XYZ::aaa << endl;



	//fara op. rezolutie
	using namespace XYZ;
	nume = "Vlad";
	cout << "XYZ::nume=" << nume << endl;

	aaa = 200;
	cout << "XYZ::aaa=" << XYZ::aaa << endl;
}