
#include "stdafx.h"

int temp[100];
int buf[100];
int match_num[100];
int cur_case = 0;

void Comb(int n, int r, int q, int sum_num) {
	if (r == 0) {
		int sum = 0;
		for (int i = q - 1; i >= 0; i--) {
			sum += temp[i];
		}
		if (sum == sum_num)
			match_num[cur_case]++;
		return;
	}
	else if (n<r) {
		return;
	}
	else {
		temp[r - 1] = buf[n - 1];
		Comb(n - 1, r - 1, q, sum_num);
		Comb(n - 1, r, q, sum_num);
	}
}

int Comb_sun() {
	int T, N, V;
	do {
		scanf("%d", &T);
	} while (T < 1 || T > 100);

	for (cur_case = 0; cur_case < T; cur_case++) {
		do {
			scanf("%d", &N);
		} while (N < 1 || N > 100);

		int i = 0;
		while (i< N)
		{
			scanf("%d", &buf[i++]);
		}

		scanf("%d", &V);

		Comb(N, 4, 4, V);

	}

	for (int c = 0; c < T; c++) {
		if (match_num[c] > 0)
			printf("1\n");
		else
			printf("0\n");
	}
	//code
	return 0;
}

//============================================================================
//#include <iostream>
#define MAX(X, Y)  ((X > Y) ? (X) : (Y))
int getMaxValueWithoutAdjacents(int *b, int n) {
	int incl = b[0];
	int excl = 0;
	int new_ex = 0;

	for (int i = 1; i < n; i++) {
		new_ex = MAX(incl, excl);
		incl = excl + b[i];
		excl = new_ex;
	}
	return MAX(incl, excl);
}


int MaxSumWithoutAdjacents() {
	int buf[100];
	int maxval[100];
	int T, N, V;
	do {
		scanf("%d", &T);
	} while (T < 1 || T > 80);

	for (int i = 0; i < T; i++) {
		do {
			scanf("%d", &N);
		} while (N < 1 || N > 100);

		int k = 0;
		while (k< N)
		{
			do {
				scanf("%d", &buf[k]);
			} while (buf[k] < 1 || buf[k] > 500);
			k++;
		}

		maxval[i] = getMaxValueWithoutAdjacents(buf, N);
	}

	for (int c = 0; c < T; c++) {
		printf( "%d\n", maxval[c] );
	}
	//code
	return 0;
}
