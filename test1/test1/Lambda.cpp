#include "stdafx.h"
#include "Lambda.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>		//stringstream
#include <list>
#include <tuple>

using namespace std;

tuple<int, double, string> getTupleData()
{
	return make_tuple(1, 2.3, "This is tuple!");
}

void test_lambda_tuple() {
	auto f = [](int x, int y) {	return x + y; };
	cout << "Test Lambda : " << f(2, 3) << endl;

	auto t = make_tuple(7, 2.3, "value");
	cout << "Test Tuple 1: " << get<0>(t) << get<1>(t) << get<2>(t) << endl;
	auto t2 = getTupleData();
	cout << "Test Tuple 2: " << get<0>(t2) << get<1>(t2) << get<2>(t2) << endl;

}
void test_find_if() {
	list<int> nums;

	nums.push_back(13);
	nums.push_back(17);
	nums.push_back(42);
	nums.push_back(46);
	nums.push_back(99);

	const list<int>::const_iterator r =
		find_if(nums.begin(), nums.end(), [](int n) { return n % 2 == 0; });
	if (r != nums.end()) {
		cout << "The first even number in the list is " << *r << "." << endl;
	}
	else {
		cout << "The list contains no even numbers." << endl;
	}
}