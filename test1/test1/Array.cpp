#include "stdafx.h"
#include "Array.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


struct eleCount {
	int e;
	int c;
};


void moreThanNdK(int arr[], int n, int k) {
	if (k < 2)	return;

	vector<eleCount> temp(k - 1);
	for (int i = 0; i<k - 1; i++)
		temp[i].c = 0;

	for (int i = 0; i < n; i++)
	{
		int j;

		for (j = 0; j<k - 1; j++)
		{
			if (temp[j].e == arr[i])
			{
				temp[j].c += 1;
				break;
			}
		}

		if (j == k - 1)
		{
			int l;

			for (l = 0; l<k - 1; l++)
			{
				if (temp[l].c == 0)
				{
					temp[l].e = arr[i];
					temp[l].c = 1;
					break;
				}
			}

			if (l == k - 1)
				for (l = 0; l<k-1; l++)
					temp[l].c -= 1;
		}
	}

	for (int i = 0; i<k - 1; i++)
	{
		int ac = 0;  // actual count
		for (int j = 0; j<n; j++)
			if (arr[j] == temp[i].e)
				ac++;

		if (ac > n / k)
			cout << "Number:" << temp[i].e << " Count:" << ac << endl;
	}
}

void swap(int *x, int *y);
class clsHeap
{
	int *harr = NULL;  
	int size; 
	int rsize; 

	int parent(int i) { return (i - 1) / 2; }
	int childL(int i) { return i * 2 + 1; }
	int childR(int i) { return i * 2 + 2; }
public:
	clsHeap(int capacity) {
		size = 0;
		rsize = capacity;
		harr = new int[capacity];
	}
	~clsHeap() { if (harr != NULL)	delete harr; }

	void insertMin(int k) {
		if (size == rsize)
		{
			cout << "\n Heap size Overflow \n";
			return;
		}

		int i = size++;
		harr[i] = k;

		while (i != 0 && harr[parent(i)] > harr[i])
		{
			swap(&harr[i], &harr[parent(i)]);
			i = parent(i);
		}
	}
	void insertMax(int k) {
		if (size == rsize)
		{
			cout << "\n Heap size Overflow \n";
			return;
		}

		int i = size++;
		harr[i] = k;

		while (i != 0 && harr[parent(i)] < harr[i])
		{
			swap(&harr[i], &harr[parent(i)]);
			i = parent(i);
		}
	}

	int *getHeap() { return harr; }
};


void checkHeap(int *nums, int s, int k) {
	if (s < k) {
		cout << "LIST IS OF LESSER SIZE";
		return;
	}
	clsHeap h(s);
	for (int i = 0; i < s; i++) {
		h.insertMin(nums[i]);
	}
	int *B = h.getHeap();
	for (int j = 0; j < k; j++) {
		cout << B[j];
		if (j != k - 1)		cout << ",";
	}
	cout << endl;

}


void runNDK()
{
	cout << "First Test\n";
	int arr0[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int size0 = sizeof(arr0) / sizeof(arr0[0]);
	checkHeap(arr0, size0, 3);
	checkHeap(arr0, size0, 10);
	/*
	cout << "First Test\n";
	int arr1[] = { 4, 5, 6, 7, 8, 4, 4 };
	int size = sizeof(arr1) / sizeof(arr1[0]);
	int k = 3;
	moreThanNdK(arr1, size, k);

	cout << "\nSecond Test\n";
	int arr2[] = { 4, 2, 2, 7 };
	size = sizeof(arr2) / sizeof(arr2[0]);
	k = 3;
	moreThanNdK(arr2, size, k);

	cout << "\nThird Test\n";
	int arr3[] = { 2, 7, 2 };
	size = sizeof(arr3) / sizeof(arr3[0]);
	k = 2;
	moreThanNdK(arr3, size, k);

	cout << "\nFourth Test\n";
	int arr4[] = { 2, 3, 3, 2 };
	size = sizeof(arr4) / sizeof(arr4[0]);
	k = 3;
	moreThanNdK(arr4, size, k);
	*/
}

int getMaxSubtractionTwoNum(int *a, int s) {
	int r = 0, i,j;
	for (i = 0; i < s; i++) {
		for (j = i + 1; j < s; j++) {
			if (a[j] > a[i] && r < j - i)
				r = j - i;
		}
	}

	return r;
}

void run_getMaxSubtractionTwoNUm() {
	int a[] = { 9, 2, 3, 4, 5, 6, 7, 8, 18, 0 };
	cout << "{9, 2, 3, 4, 5, 6, 7, 8, 18, 0} = j-i : "
		<< getMaxSubtractionTwoNum(a, sizeof(a) / sizeof(int)) << endl;
}

