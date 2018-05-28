// test1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include "sort.h"
#include "linkedlist.h"
#include "BinaryString.h"
#include "subset.h"
#include "Calculate.h"
#include "Palindrome.h"
#include "TextInput.h"
#include "Lambda.h"
#include "Substring.h"
#include "integer.h"
#include "Array.h"
#include "Trees.h"
#include "Matrix.h"
#include "TowerHopper.h"
#include "search_string.h"
#include "search.h"

void print_data(int *d, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", d[i]);
	}
	printf("\n");
}

int numdata[9] = { 11, 3, 20, 1, 59, 600, 71, 18, 92 };

extern int test2();
extern void permutation(int n, int s, int q);
extern void Combination(int n, int s, int q);
extern void comb(int n, int s, int q);
extern int MaxSumWithoutAdjacents();



int main(void) {
//	permutation(6, 4, 4);
	//printf("=======================\n");
	//Combination(6, 4, 4);
	//comb(6, 0, 4);
	//test2();
	int num = sizeof(numdata) / sizeof(int);
//	mergeSort(numdata, 0, num -1);

	//quickSort(numdata, 0, num - 1);
	//radixsort(numdata, num);
	//MaxSumWithoutAdjacents();
	//print_data(numdata, num);
	//Most_frequent_word_in_an_array_of_strings();
	//Segregate_even_and_odd();
	//CuttingBinaryString();

	//run_subset();

	//CalculateWithoutPlus(4, 6);
	//runMergeSortArray();

	//std::cout << Palindrome::isPalindrome("Deleveled");
	
	//test_find_if();
	//test_lambda_tuple();

	//run_findMedianSortedArrays();
	//run_addTwoNumbers();

	//run_Palindrome();
	
	//runSubstring();

	//run_ReverseInteger();
	//run_AtoI();
	//runFloatToBin(10.825);
	//runNDK();
	//run_swapping_kth_nodes();
	//run_tree();

	//run_getMaxSubtractionTwoNum();

	//runSubString();

	//runMatrix();
	//runAmazonTest();

	//runCalculate();

	//run_sort();
	//runTowerHoppper();

	//run_search_string();
	runSearch();
}

