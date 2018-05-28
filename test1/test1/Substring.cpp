#include "stdafx.h"
#include "Substring.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int lengthOfLongestSubstring(string s) {
	int r = 0;

	vector<int> str_chk(128, -1);
	int offset = -1;

	for(int i = 0; i < s.length(); i++) {
		if (str_chk[s[i]] > offset)
			offset = str_chk[s[i]];
		str_chk[s[i]] = i;
		r = max(r, i - offset);
	}
	return r;
}

//Given "abcabcbb", the answer is "abc", which the length is 3.
//Given "bbbbb", the answer is "b", with the length of 1.
//Given "pwwkew", the answer is "wke", with the length of 3.

void getSubstring() {
	string s[] = { "a", "1", "pwwkew", "bbbbb", "abcabcbb" };

	for (string v : s) {
		int ret = lengthOfLongestSubstring(v);
		string out = to_string(ret);
		cout << v << " : " << out << endl;
	}
}




string convert(string s, int numRows) {
	if (numRows == 1) {
		return s;
	}

	vector<string> arrS(numRows);

	int curRow = 0;
	int inc = -1;
	for (char ch : s) {
		arrS[curRow] += ch;
		if (curRow == 0 || curRow == numRows - 1) {
			inc *= -1;
		}
		curRow += inc;
	}

	string r;
	for (string s : arrS) {
		r += s;
	}
	return r;
}

void run_convert() {
	cout << convert("PAYPALISHIRING", 3) << endl;
	cout << convert("PAYPALISHIRING", 4) << endl;
}


bool isMatch(const string& s, int i, const string& p, int j) {
	if (s.length() == i) {
		return p.length() == j
			|| (p.length() > j + 1 && p[j + 1] == '*' && isMatch(s, i, p, j + 2));
	}

	if (p.length() > j + 1 && p[j + 1] == '*') {
		if (s[i] == p[j] || p[j] == '.') {
			return isMatch(s, i + 1, p, j) || isMatch(s, i, p, j + 2);
		}
		else {
			return isMatch(s, i, p, j + 2);
		}
	}
	else {
		if (s[i] == p[j] || p[j] == '.') {
			return isMatch(s, i + 1, p, j + 1);
		}
		else {
			return false;
		}
	}
}


bool isMatch(string s, string p) {
	return isMatch(s, 0, p, 0);
}

void run_isMatch() {
	vector<pair<string, string>> vec_pair = {make_pair("aab", "c*a*b"), 
		make_pair("ab", ".*") };
	for (pair<string, string> p : vec_pair) {
		cout << p.first << " : " << isMatch(p.first, p.second) << endl;
	}

}



//Remove Alternate Duplicate characters from a char array you have to do it in Place.Like keeping only the odd occurences of each character.
//Example: Input: ¡°you got beautiful eyes¡±
//Output : ¡±you gtbeaiful es¡±
//Allowed Time Complexity was O(n) and Space Complexity was O(1)

string removeDuplicate(string s) {
	string r;
	char ch_bit[127];
	memset(ch_bit, 0, 127);
	for(char c : s){
		if (ch_bit[c] == 0) {
			r += c;
		}
		ch_bit[c] = !ch_bit[c];
	}
	return r;
}

void run_removeDuplicate() {
	cout << removeDuplicate("you got beautiful eyes") << endl;
	cout << removeDuplicate("In a file there are 1 million words.") << endl;
}


//You are given an string as input which represents a path.You have to normalize that path inplace(NO EXTRA SPACE).
//e.g.
//input : "\a\b\c\..\..\file.txt"
//output : "\a\file.txt"


string getNormalizedPath(string s){
	string r, cpath;
	vector<string> paths;

	s.erase(s.begin(), find_if(s.begin(), s.end(),
		[](int n) { return !isspace(n); }) );
	s.erase(find_if(s.rbegin(), s.rend(),
		[](int n) { return !isspace(n); }).base(), 
		s.end());
	
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '/' || s[i] == '\\') {
			if (cpath.size() == 0)	continue;
			if (cpath == "..") {
				if (paths.size() > 0)	paths.pop_back();
			}
			else {
				paths.push_back(cpath);
			}
			cpath.clear();
		}
		else {
			cpath += s[i];
		}
	}
	if (!cpath.empty()) paths.push_back(cpath);

	if (paths.empty())	return "/";
	for (string p : paths) {
		r.append("/" + p);
	}
	
	return r;
}

void runSubString() {
	cout << getNormalizedPath("\\a\\b\\c\\..\\..\\file.txt") << endl;
}