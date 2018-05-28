#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>		//stringstream
#include <list>
#include <tuple>
#include <ctime>

#include <set>

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
	vector<int> r(2);
	for (int i = 0; i < (int)nums.size(); i++) {
		for (int j = i+1; j < (int)nums.size(); j++) {
			if (nums[i] + nums[j] == target) {
				r[0] = i;
				r[1] = j;
				return r;
			}
		}
	}
	return r;
}

bool HasPairWithSum(vector<int>& num, int key) {
	set<int> comp;

	for (int v : num) {
		if (comp.find(v) != comp.end())
			return true;

		comp.insert(key - v);
	}
	return false;
}

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

		vector<int> ret = twoSum(nums, target);

		string out = integerVectorToString(ret);
		cout << out << endl;
	}
	return 0;
}


//====================================================
struct ListNode {
    int val;
	ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int carry = 0;
	ListNode *head = new ListNode(0);
	ListNode *curN = head, *n1 = l1, *n2 = l2;
	while (n1 != NULL || n2 != NULL || carry != 0) {
		int x = 0, y = 0;
		if (n1 != NULL) {
			x = n1->val;
			n1 = n1->next;
		}
		if (n2 != NULL) {
			y = n2->val;
			n2 = n2->next;
		}
		int sum = carry + x + y;
		carry = sum / 10;
		curN->next = new ListNode(sum % 10);
		curN = curN->next;
	}
	return head->next;
}



ListNode* stringToListNode(string input) {
	// Generate list from the input
	vector<int> list = stringToIntegerVector(input);

	// Now convert that list into linked list
	ListNode* dummyRoot = new ListNode(0);
	ListNode* ptr = dummyRoot;
	for (int item : list) {
		ptr->next = new ListNode(item);
		ptr = ptr->next;
	}
	ptr = dummyRoot->next;
	delete dummyRoot;
	return ptr;
}

string listNodeToString(ListNode* node) {
	if (node == nullptr) {
		return "[]";
	}

	string result;
	while (node) {
		result += to_string(node->val) + ", ";
		node = node->next;
	}
	return "[" + result.substr(0, result.length() - 2) + "]";
}


void ElapsedTimeAdd(float num) {
	clock_t begin = clock();
	float k = 0;
	int n = (int)num;
	for (size_t i = 0; i < n; i++) {
		k = k + 1.01f;
	}

	clock_t end = clock();
	cout << "ElapsedTime added float  : " << (float)(end - begin)/CLOCKS_PER_SEC << endl;
}
void ElapsedTimeAdd(int num) {
	clock_t begin = clock();
	int k = 0;
	for (size_t i = 0; i< num; i++) {
		k = k + 1;
	}

	clock_t end = clock();
	cout << "ElapsedTime added integer : " << (float)(end - begin) / CLOCKS_PER_SEC << endl;
}


void ElapsedTimeDivid(float num) {
	clock_t begin = clock();
	float k = 0;
	int n = (int)num;
	for (size_t i = 0; i < n; i++) {
		k = 10 / 1.01f;
	}

	clock_t end = clock();
	cout << "ElapsedTime divided float  : " << (float)(end - begin) / CLOCKS_PER_SEC << endl;
}

void ElapsedTimeDivid(int num) {
	clock_t begin = clock();
	int k = 1000000;
	for (size_t i = 0; i< num; i++) {
		k = 10/2;
	}

	clock_t end = clock();
	cout << "ElapsedTime divided integer : " << (float)(end - begin) / CLOCKS_PER_SEC << endl;
}

void run_addTwoNumbers() {
	ListNode* l1 = stringToListNode("[2,4,3]");
	ListNode* l2 = stringToListNode("[5,6,4]");

	ListNode* ret = addTwoNumbers(l1, l2);

	string out = listNodeToString(ret);
	cout << out << endl;
}

void runCalculate() {
	//run_addTwoNumbers();
	//ElapsedTimeAdd(10000000);
	//ElapsedTimeAdd(10000000.0f);
	//ElapsedTimeDivid(10000000);
	//ElapsedTimeDivid(10000000.0f);

	int a[7] = { 1, 2, 3, 4, 6, 7, 8 };
	vector<int> v(a, a + 7);
	cout << HasPairWithSum(v, 8);
}

