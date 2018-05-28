#include "stdafx.h"
#include "search_string.h"
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;


struct word_info {
	char *word;
	int cnt;
};

void Most_frequent_word_in_an_array_of_strings() {
	char buf[1000][100];
	char result[100][100];
	int T, N;
	struct word_info  winfo[1000];

	do {
		scanf("%d", &T);
	} while (T < 1 || T > 100);

	for (int i = 0; i < T; i++) {
		do {
			scanf("%d", &N);
		} while (N < 1 || N > 1000);

		int k = 0;
		while (k< N)
		{
			scanf("%s", buf[k]);
			winfo[k].word = buf[k];
			winfo[k].cnt = 0;
			k++;
		}

		for (int n = 0; n < N; n++) {
			for (int n2 = 0; n2 < N; n2++) {
				if (strcmp(winfo[n].word, buf[n2]) == 0) {
					winfo[n].cnt++;
				}
			}
		}

		int max_freq = winfo[0].cnt;
		char *max_word = winfo[0].word;
		strcpy(result[i], winfo[0].word);
		for (int n = 1; n < N; n++) {
			if (max_freq <= winfo[n].cnt) {
				if (max_freq == winfo[n].cnt && strcmp(max_word, winfo[n].word) < 0)
					continue;
				max_word = winfo[n].word;
				max_freq = winfo[n].cnt;
				strcpy(result[i], winfo[n].word);
			}
		}
		//printf("%s  :  %d\n", winfo[result[i]].word, winfo[result[i]].cnt);
	}
	for (int i = 0; i < T; i++) {
		printf("%s\n", result[i]);
	}
}



pair<char, int> getLogestConsecutiveCharacters(string s) {
	char prev = -1;
	int cnt = 0;
	pair<char, int> r = make_pair(-1, 0);
	for (char c : s) {
		if (c != prev) {
			if (r.second < cnt) {
				r.first = prev;
				r.second  = cnt;
			}
			prev = c;
			cnt = 1;
		}
		else {
			cnt++;
		}
	}
	if (r.second < cnt) {
		r.first = prev;
		r.second = cnt;
	}

	return r;
}



//	Longest common substring for Dynamic Programming	
string s1 = "AACD", s2 = "ABBBCD", s3;
char memo[20][20];
int LCS_DP_recurtion(int i1, int i2) {
	if (i1 == s1.length() || i2 == s2.length()) 
		return 0;
	if (s1[i1] == s2[i2]) {
		if (memo[i1][i2] == -1) {
			memo[i1][i2] = 1 + LCS_DP_recurtion(i1 + 1, i2 + 1);
		}
		return memo[i1][i2];
	}
	else {
		if (memo[i1][i2 + 1] == -1) {
			memo[i1][i2 + 1] = LCS_DP_recurtion(i1, i2 + 1);
		}

		if (memo[i1 + 1][i2] == -1) {
			memo[i1 + 1][i2] = LCS_DP_recurtion(i1 + 1, i2);
		}
		return max(memo[i1][i2 + 1], memo[i1 + 1][i2]);
	}
}
int LCS_DP_for() {
	for (int i = 0; i <= s1.length(); i++) {
		for (int j = 0; j <= s2.length(); j++) {
			if (i == 0 || j == 0) {
				memo[i][j] = 0;
			}
			else if(s1[i-1] == s2[j-1]){
				memo[i][j] = 1 + memo[i - 1][j - 1];
			}
			else {
				memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
			}
		}
	}

	return memo[s1.length()][s2.length()];
}

void run_search_string() {
	//string s = "abssssadess";
	//pair<char, int> r = getLogestConsecutiveCharacters(s);
	//cout << "char : " << r.first << ", count : " << r.second;
	memset(memo, -1, 400);
	int n = LCS_DP_recurtion( 0, 0);
	n = LCS_DP_for();
	cout << "s1 =" << s1 << ", s2 = " << s2 << ", LCS :" << n << " string =  " << s3;
}