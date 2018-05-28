#include "stdafx.h"
#include "sort.h"
#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

extern void swap(int* a, int* b);

//#define def_swap(x, y) x ^= y ^= x ^= y

//O(n^2)   -> Selection, Insertion, Bubble
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}
//==================================================================
//  O(NlogN) --> quick, Merge, Heap 
vector<int> mergeSortedArray(vector<int> &A, vector<int> &B) {
	vector<int> r;
	int i = 0, j = 0;

	while (i < A.size() && j < B.size()) {
		if (A[i] < B[j]) {
			r.push_back(A[i++]);
		}
		else {
			r.push_back(B[j++]);
		}
	}
	while (i < A.size()) {
		r.push_back(A[i++]);
	}
	while (j < B.size()) {
		r.push_back(B[j++]);
	}

	return r;
}
vector<int> mergeSortedArray(vector<int> a) {
	if (a.size() < 2)	return a;
	int mid = a.size() / 2;
	int l = mid, r = a.size() - mid;
	vector<int> vl, vr;

	for (int i = 0; i < mid; i++) {
		vl.push_back(a[i]);
	}
	for (int i = mid; i < a.size(); i++) {
		vr.push_back(a[i]);
	}
	vector<int> r1 = mergeSortedArray(vl);
	vector<int> r2 = mergeSortedArray(vr);
	return mergeSortedArray(r1, r2);
}


void runMergeSortArray() {
	int a[] = { 1, 7, 3, 4, 11 };
	int b[] = { 2, 4, 5, 6 };
	int sa = sizeof(a) / sizeof(a[0]);
	int sb = sizeof(b) / sizeof(b[0]);
	vector<int> v1(a, a + sa);
	vector<int> v2(b, b + sb);

	vector<int> r = mergeSortedArray(mergeSortedArray(v1), mergeSortedArray(v2));

	for (int i : r) {
		printf("%d ,", i);
	}
}




void quickSort(int data[], int l, int r) {
	int p = l, j = l, i = l;
	if (l < r) {
		while(++i <= r) {
			if (data[i] < data[p]) {
				swap(&data[++j], &data[i]);
			}
		}
		swap(&data[p], &data[j]);
		p = j;
		quickSort(data, l, p - 1);
		quickSort(data, p + 1, r);
	}
}

void runQuickSort() {
	int arr[7] = { 5,3, 7, 6, 1 , 2 ,4 };
	for (int i = 0; i < 7; i++) printf("%d ", arr[i]);
	printf("\n");
	quickSort(arr, 0, 6);
	for (int i = 0; i < 7; i++) printf("%d ", arr[i]);
}


void heapify(int arr[], int n, int i) {
	int p = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[p]) p = l;
	if (r < n && arr[r] > arr[p]) p = r;
	if (p != i) {
		swap(arr[i], arr[p]);
		heapify(arr, n, p);
	}
}
void heapSort(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}
	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}



void HeapSearchFor(int arr[], int n) {
	for (int i = 1; i < n; i++) {
		int c = i;
		do {
			int p = (c - 1) / 2;
			if (arr[p] < arr[c]) {
				swap(arr[p], arr[c]);
			}
			c = p;
		} while (c != 0);
	}
	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		int p = 0;
		int c = 1;
		do {
			c = 2 * p + 1;
			if (arr[c] < arr[c + 1] && c < i - 1) {
				c++;
			}
			if (arr[p] < arr[c] && c < i) {
				swap(arr[p], arr[c]);
			}
			p = c; 
		} while (c < i);
	}
}


void run_HeapSearch() {
	int arr[7] = { 5,3, 7, 6, 1 , 2 ,4 };
	for (int i = 0; i < 7; i++) printf("%d ", arr[i]);
	printf("\n");
	//HeapSearchFor(arr, 7);
	heapSort(arr, 7);
	for (int i = 0; i < 7; i++) printf("%d ", arr[i]) ;
}

//==================================================================
using namespace std;

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
	const int const_n = n;
//	int output[n]; // output array
	int output[10]; // output array
	int i, count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using 
// Radix Sort
void radixsort(int arr[], int n)
{
	// Find the maximum number to know number of digits
	int m = getMax(arr, n);

	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 10^i
	// where i is current digit number
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}




double findMedianSortedArrays(int *A, int sA, int *B, int sB) {
	int m = sA;
	int n = sB;
	if (m > n) {
		int* temp = A; A = B; B = temp;
		int tmp = m; m = n; n = tmp;
	}
	int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;
	while (iMin <= iMax) {
		int i = (iMin + iMax) / 2;
		int j = halfLen - i;
		if (i < iMax && B[j - 1] > A[i]) {
			iMin = iMin + 1; // i is too small
		}
		else if (i > iMin && A[i - 1] > B[j]) {
			iMax = iMax - 1; // i is too big
		}
		else { // i is perfect
			int maxLeft = 0;
			if (i == 0) { maxLeft = B[j - 1]; }
			else if (j == 0) { maxLeft = A[i - 1]; }
			else { maxLeft = max(A[i - 1], B[j - 1]); }
			if ((m + n) % 2 == 1) { return maxLeft; }

			int minRight = 0;
			if (i == m) { minRight = B[j]; }
			else if (j == n) { minRight = A[i]; }
			else { minRight = min(B[j], A[i]); }

			return (maxLeft + minRight) / 2.0;
		}
	}
	return 0.0;
}

double findMedianSortedArrays2(int *A, int sA, int *B, int sB) {
	int sC = sA + sB;
	int *C = new int[sC];
	int i = 0, j = 0, k = 0;

	while (i < sA || j < sB) {
		int a = INT32_MAX, b = INT32_MAX;

		if (i < sA)	a = A[i];
		if (j < sB) b = B[j];
		if (a < b) {
			C[k] = a;
			i++;
		}
		else {
			C[k] = b;
			j++;
		}
		k++;
	}

	if (sC % 2 == 1) 		return C[sC / 2];
	else		return (C[(sC / 2) - 1] + C[(sC / 2)]) / 2.0;
}


void run_findMedianSortedArrays() {
	int a[] = { 1, 3 };
	int b[] = { 2, 4, 5, 10 };
	
	double mid = findMedianSortedArrays(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[1]));
	double mid2 = findMedianSortedArrays2(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[1]));

	cout << "mid1 : " << mid << endl;
	cout << "mid2 : " << mid << endl;
}


void run_sort() {
	//runMergeSortArray();
	//runQuickSort();
	run_HeapSearch();
	//	run quick sort

}