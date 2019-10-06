#include "pch.h"
#include <iostream>

using namespace std;

double suma(int x, double y) {
	return x + y;
}

void fct1(int x, int y) {
	x = x + y;
}

void fct2(int &x, int &y) {
	x = x + y;
	y = 1210321;
}
int main()
{
	cout << "Hello World!\n";


	int a = 1;
	double b = 20.43;
	int c = 2;
	cout << suma(a, c);


	////////////////////////////
	int t = 10, u = 20;
	fct1(t, u);
	cout << endl << "\n" << t << " " << u;

	fct2(t, u);
	cout << endl << "\n" << t << " " << u;
}