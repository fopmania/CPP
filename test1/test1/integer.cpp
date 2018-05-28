#include "stdafx.h"
#include "integer.h"
#include <iostream>
#include <string>

using namespace std;


int reverse(int x) {
	long r = 0;
	while (x != 0) {
		r = (r * 10) + (x % 10);
		if (r > INT32_MAX || r < INT32_MIN) return 0;
		x /= 10;
	}
	return r;
}


void run_ReverseInteger() {
	cout << reverse(-123) << endl;
}

int AtoI(string str) {
	long r = 0;
	int sign = 1;
	int offset = str.find_first_not_of(' ');

	if (str[offset] == '-' || str[offset] == '+') {
		sign = (str[offset++] == '-') ? -1 : 1;
	}
	while (str[offset] >= '0' && str[offset] <= '9') {
		r = r * 10 + (str[offset++] - '0');
		if (r * sign >= INT32_MAX)	return INT_MAX;
		if (r *sign <= INT32_MIN)	return INT_MIN;
	}

	return r*sign;
}

void run_AtoI() {
	cout << AtoI("2147483646") << endl;
	cout << AtoI("9223372036854775808") << endl;
	cout << AtoI("4193 with words") << endl;
	cout << AtoI("+-2") << endl;
	cout << AtoI("3.14159") << endl;
	cout << AtoI("words and 987") << endl;
}
