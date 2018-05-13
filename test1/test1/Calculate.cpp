#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>		//stringstream
#include <list>
#include <tuple>
using namespace std;

void CalculateWithoutPlus(int a, int b) {

	int jw = a&b;
	int jg = a^b;
	while (jw > 0)
	{
		int ta = jg;
		int tb = jw << 1;
		jw = ta & tb;
		jg = ta ^ tb;
	}
	printf("%d + %d = %d", a, b, jg);

}

vector<int> twoSum(vector<int>& nums, int target) {
	vector<int> r;
	for (int i = 0; i < nums.size(); i++) {
		for (int j = i + 1; j < nums.size(); j++) {
			if (nums[i] + nums[j] == target) {
				r.push_back(i);
				r.push_back(j);
			}
		}
	}
	return r;
}


class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> r;
		for (int i = 0; i < nums.size(); i++) {
			for (int j = 1; j < nums.size(); j++) {
				if (nums[i] + nums[j] == target) {
					r.push_back(i);
					r.push_back(j);
				}
			}
		}
		return r;
	}
};

void trimLeftTrailingSpaces(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
	}));
}

void trimRightTrailingSpaces(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
	vector<int> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	char delim = ',';
	while (getline(ss, item, delim)) {
		output.push_back(stoi(item));
	}
	return output;
}

int stringToInteger(string input) {
	return stoi(input);
}

string integerVectorToString(vector<int> list, int length = -1) {
	if (length == -1) {
		length = list.size();
	}

	if (length == 0) {
		return "[]";
	}

	string result;
	for (int index = 0; index < length; index++) {
		int number = list[index];
		result += to_string(number) + ", ";
	}
	return "[" + result.substr(0, result.length() - 2) + "]";
}

int run_twoSum() {
	string line;
	while (getline(cin, line)) {
		vector<int> nums = stringToIntegerVector(line);
		getline(cin, line);
		int target = stringToInteger(line);

		vector<int> ret = Solution().twoSum(nums, target);

		string out = integerVectorToString(ret);
		cout << out << endl;
	}
	return 0;
}




//======== lambda find_if
void test_lambda_tuple() {
	auto f = [](int x, int y) {	return x + y; };
	cout << "Test Lambda : " << f(2, 3) << endl;

	auto t = make_tuple(7, 2.3, "value");
	cout << "Test Tuple 1: " << get<0>(t) << get<1>(t) << get<2>(t) << endl;


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
	if(r != nums.end()){
		cout << "The first even number in the list is " << *r << "." << endl;
	}
	else {
		cout << "The list contains no even numbers." << endl;
	}
}