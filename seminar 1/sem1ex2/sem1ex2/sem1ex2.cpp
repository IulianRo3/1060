
#include "pch.h"
#include <iostream>

using namespace std;
int main()
{
	cout << "Hello World!\n";

	int v[3] = { 1,2,3 }, w[2], aaa[4];

	cout << v[1] << endl;

	w[1] = 120;
	cout << w[1] << endl;

	cout << "citire vector aaaa" << endl << endl;
	for (int i = 0; i < 4; i++) {
		cout << "aaa[" << i << "]=";
		cin >> aaa[i];
	}

	for (int i = 0; i < 4; i++) {
		cout << "aaa[" << i << "]=" << aaa[i] << " ";
	}
}