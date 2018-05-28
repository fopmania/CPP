#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include <bitset>

using namespace std;

int binConv(char *bin)
{
	int dec = 0;
	int len = strlen(bin);
	for (int c = 0; c < len; c++)
	{
		if (bin[len - c - 1] == '1')
			dec = (dec +  pow(2.0, c));
		else
			dec = (dec + pow(0.0, c));
	}
	return dec;
}

int checkPowerOf5(char *str) {
	int len = strlen(str);
	int cnt = 0;
	char temp[51];
	int begin = 0;
	for (int i = 0; i < len; i++) {
		memset(temp, 0, 51);
		strncpy(temp, str + begin, i+1 - begin);
		//unsigned long n = std::bitset<50>(temp).to_ulong();
		unsigned long n = binConv(temp);
		for (int p = 1; p < 20; p++) {
			if (pow(5, p) > n)	break;
			if (n / pow(5, p) == 1){
				begin = i + 1;
				cnt++;
				break;
			}
		}
	}
	if (cnt > 0)		return cnt;

	return -1;
}

int CuttingBinaryString() {
	char buf[10][50];
	int result[10];
	int T;
	do {
		scanf("%d", &T);
	} while (T < 1 || T > 80);

	for (int i = 0; i < T; i++) {
		struct Node *head = NULL;
		do {
			scanf("%s", &buf[i]);
		} while ( strlen(buf[i]) < 1 || strlen(buf[i]) > 50 );
		result[i] = checkPowerOf5(buf[i]);
	}

	for (int c = 0; c < T; c++) {
		printf("%d\n", result[c]);
	}
	//code
	return 0;
}



//====================================================
int findSubArray(char *arr, int n)
{
	int sum = 0;
	int maxsize = -1, startindex;

	for (int i = 0; i < n - 1; i++)
	{
		sum = (arr[i] == '0') ? -1 : 1;

		for (int j = i + 1; j < n; j++)
		{
			(arr[j] == '0') ? sum += -1 : sum += 1;

			if (sum == 0 && maxsize < j - i + 1)
			{
				maxsize = j - i + 1;
				startindex = i;
			}
		}
	}
	if (maxsize == -1)
		printf("No such subarray");
	else
		printf("%d to %d", startindex, startindex + maxsize - 1);

	return maxsize;
}

int Longest_substring_with_equal_number() {
	char buf[10][50];
	int result[10];
	int T;
	do {
		scanf("%d", &T);
	} while (T < 1 || T > 80);

	for (int i = 0; i < T; i++) {
		struct Node *head = NULL;
		do {
			scanf("%s", &buf[i]);
		} while (strlen(buf[i]) < 1 || strlen(buf[i]) > 50);
		result[i] = findSubArray(buf[i], sizeof(buf[i]));
	}

	for (int c = 0; c < T; c++) {
		printf("%d\n", result[c]);
	}
	//code
	return 0;
}


void runFloatToBin(float a)
{
	int  integral, binaryInt = 0, i = 1;
	float  binaryFract = 0, k = 0.1f, fractional, temp1, binaryTotal;

	integral = (int)a;

	fractional = a - (int)a;

	while (integral>0)
	{
		binaryInt = binaryInt + (integral % 2) * i;
		i = i * 10;
		integral = integral / 2;
	}

	while (k>0.00000001)
	{
		temp1 = fractional * 2;
		binaryFract = binaryFract + ((int)temp1)*k;
		fractional = temp1 - (int)temp1;
		k = k * 0.1f;
	}

	binaryTotal = (float)binaryInt + binaryFract;
	printf("float : %f = Binary : %f", a, binaryTotal);
}