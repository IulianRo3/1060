#include "pch.h"
#include <iostream>

using namespace std;
int main()
{
	cout << "Hello World!\n";

	int jd = 100;
	int *x = new int;
	int *y = new int(10);

	cout << *y;


	//dezalocare variabila
	delete x;
	delete y;

	///////////////////////////////
	int *xx = new int[4];
	int k = 0;
	for (int i = 0; i < 4; i++) {
		xx[i] = k++;
	}

	cout << endl << endl;

	//dezalocare vector
	for (int i = 0; i < 4; i++) {
		cout << xx[i]<<" ";
	}
	delete[]xx;

	///////////////////////////
	int n = 2;

	int **aaa;
	aaa = new int*[n];

	cout << endl << endl;

	for (int i = 0; i < n; i++) {
		aaa[i] = new int[n];
		for (int j = 0; j < n; j++) {
			aaa[i][j] = k++;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << aaa[i][j] << " ";
		}
		cout << endl;
	}

	//dezalocare matrice
	for (int i = 0; i < n; i++) {
		delete aaa[i];
	}

	delete[] aaa;
}