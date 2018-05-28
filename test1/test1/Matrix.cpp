#include "stdafx.h"
#include "Matrix.h"
#include <iostream>

using namespace std;

//Rotate a M*N matrix by 90 degree.

const int Dim = 4;

void printMatrix(int m[Dim][Dim]) {
	int s = Dim;
	for(int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void rotate90degree(int m[Dim][Dim]) {
	int s = Dim;
	for (int i = 0; i < s/2; i++) {
		for (int j = i; j < s - i - 1; j++) {
			int t = m[i][j];
			m[i][j] = m[j][s - i - 1];					//	r -> t
			m[j][s - i - 1] = m[s - i - 1][s - j - 1];	//	b -> r
			m[s - i - 1][s - j - 1] = m[s - j - 1][i];	//	l -> b
			m[s - j - 1][i] = t;

			printMatrix(m);
		}
	}

}




void runMatrix() {
	int m[Dim][Dim] = { {1,  2,  3, 4},
						{5,  6,  7,  8},
						{9, 10, 11, 12},
						{13, 14, 15, 16} };


	rotate90degree(m);
}
