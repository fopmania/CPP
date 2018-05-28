#include "stdafx.h"
#include "AmazonTest.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;


bool isExclude(vector<string> excludes, string word) {
	for (string s : excludes) {
		if (s.compare(word) == 0)
			return true;
	}
	return true;
}
/*
vector<string> split(const string& s, char delim, vector<string> excludes) {
	int i = 0;
	int pos = s.find(delim);
	string word;
	
	while (pos != string::npos) {
		word = s.substr(i, pos - i);
		if (isExclude(excludes, word))	continue;
		v.push_back();
		i = ++pos;
		pos = s.find(delim, pos);

		if (pos == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}
*/

struct stTrie {
	string key;
	int cnt;
	map<char, stTrie*> tmap;
};

stTrie* getNewstTrieNode()
{
	stTrie* node = new stTrie;
	node->cnt = 0;
	return node;
}

void insert(stTrie*& root, string &str)
{
	stTrie* temp = root;

	for (int i = 0; i<str.length(); i++) {

		char x = str[i];

		/*a new node if path doesn't exists*/
		if (temp->tmap.find(x) == temp->tmap.end())
			temp->tmap[x] = getNewstTrieNode();

		// go to next node
		temp = temp->tmap[x];
	}

	// store key and its count in leaf nodes
	temp->key = str;
	temp->cnt += 1;
}

bool preorder(stTrie* temp, int maxcnt, string& key)
{
	if (temp == NULL)
		return false;

	for (auto it : temp->tmap) {

		if (maxcnt < it.second->cnt) {
			key = it.second->key;
			maxcnt = it.second->cnt;
		}

		preorder(it.second, maxcnt, key);
	}
}

void mostFrequentWord(string arr[], int n)
{
	stTrie* root = getNewstTrieNode();
	for (int i = 0; i < n; i++)
		insert(root, arr[i]);

	string key;
	int cnt = 0;
	preorder(root, cnt, key);

	cout << "The word that occurs most is : "
		<< key << endl;
	cout << "No of times: " << cnt << endl;
}



// FUNCTION SIGNATURE ENDS

void runAmazonTest() {

}