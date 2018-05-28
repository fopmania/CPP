#include "stdafx.h"
#include "Palindrome.h"
#include <ctype.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>      // std::pair, std::make_pair


using namespace std;



pair<int,int> getPalindrome(string s, int offset) {
	int s_cnt = min((int)s.length() - offset, offset + 1);
	int offset1 = 0, leng1 = 1;
	int offset2 = 0, leng2 = 0;
	for (int i = 1; i < s_cnt; i++) {
		if (s.at(offset - i) == s.at(offset + i) ){
			offset1 = offset - i;
			leng1 = i*2 + 1;
		}else break;
	}
	s_cnt = min((int)s.length() - offset - 1, offset + 1);
	for (int i = 0; i < s_cnt; i++) {
		if (s.at(offset - i) == s.at(offset + i + 1)) {
			offset2 = offset - i;
			leng2 = (i+1)*2;
		}else break;
	}
	pair<int, int> r;
	if (leng1 > leng2)	r = make_pair(offset1, leng1);
	else	r = make_pair(offset2, leng2);

	return r;
}

string longestPalindrome(string s) {
	int start = 0, end = 0;
	pair<int, int> result = make_pair(0, 1);
	int ln = min((int)s.length(), 1000);
	for (int i = 0; i < s.length(); i++) {
		pair<int, int> temp = getPalindrome(s, i);
		if (temp.second > result.second) {
			result = temp;
		}
	}
	return s.substr(result.first, result.second );
}


bool isPalindrome(string& word)
{
	for (int i = 0; i < word.length() / 2; i++) {
		if (tolower(word.at(i)) != tolower(word.at(word.length() - i - 1))) {
			return false;
		}
	}
	return true;
}

bool isPalindrome(int x) {
	if( x < 0 ) 
		return false;
	int r = 0, t = x;
	while (t) {
		r = r * 10 + t % 10;
		t /= 10;
	}
	return x == r;
}


void run_Palindrome() {
	//cout << longestPalindrome("cbbd") << endl;
	//cout << longestPalindrome("bb") << endl;
	//cout << longestPalindrome("a") << endl;
	//cout << longestPalindrome("babad") << endl;
	
	cout << isPalindrome(121) << endl;
}


