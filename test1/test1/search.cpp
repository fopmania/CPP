#include "stdafx.h"
#include "search.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>


using namespace std;

typedef struct nodeBST
{
	int v;
	nodeBST *left, *right;
	nodeBST(int key) {
		v = key;
		left = right = NULL;
	}
};

nodeBST* insertBST(nodeBST *n, int key) {
	if (n == NULL)	return new nodeBST(key);
	if (key < n->v)
		n->left = insertBST(n->left, key);
	else
		n->right = insertBST(n->right, key);

	return n;
}
nodeBST* searchBST(nodeBST* n, int key) {
	if (n == NULL || n->v == key)	
		return n;

	if (n->v < key)		return searchBST(n->right, key);
	return searchBST(n->left, key);
}

void deleteBST(nodeBST* n) {
	if (n == NULL)	return;

	deleteBST(n->left);
	deleteBST(n->right);

	delete n;
}

void printBST(nodeBST* n) {
	if (n == NULL)	return;

	printBST(n->left);
	cout << n->v << " ";
	printBST(n->right);

}


void runBinarySearchTree() {
	int v[6] = { 8, 3, 1, 10, 6, 7 };
	nodeBST *root = NULL;
	root = insertBST(root, v[0]);
	for (int i = 1; i < 6; i++) {
		insertBST(root, v[i]);
	}
	printBST(root);
	cout << "\n is 11 : " << (searchBST(root, 11) != NULL);
	deleteBST(root);
}

class Graph {
public:
	int n;
	vector<vector<int>> p;
	vector<bool> v;
	Graph() : n(0) {};
	Graph(int num) : n(num) {
		p.resize(num);
		v.resize(num);
	}
	void addLink(int p1, int p2) {
		p[p1].push_back(p2);
		p[p2].push_back(p1);
	}

	void dfs() {
		fill(v.begin(), v.end(), false);
		dfs(0);
	}

	void bfs() {	//	bread first search
		fill(v.begin(), v.end(), false);
		queue<int> q;
		q.push(0);
		v[0] = true;
		int level = 0;
		while (!q.empty()) {
			int qs = q.size();
			cout << " ---------- Leve : " << level << endl;
			for (int j = 0; j < qs; j++) {
				int c = q.front();
				q.pop();
				cout << " visit : " << c << endl;
				for (int i : p[c]) {
					if (!v[i]) {
						v[i] = true;
						q.push(i);
					}
				}
			}
			level++;
		}
	}

	void sortList() {
		for (int i = 0; i < n; i++) {
			sort(p[i].begin(), p[i].end());
		}


	}
private:
	void dfs(int k) {
		if (v[k])	return;
		v[k] = true;
		cout << " visit : " << k << endl;
		for (int i : p[k]) {
			dfs(i);
		}
	}
};



void runDepthFirstSearch() {
	Graph G(9);
	G.addLink(0, 2);
	G.addLink(0, 1);
	G.addLink(1, 3);
	G.addLink(1, 5);
	G.addLink(3, 4);
	G.addLink(5, 4);
	G.addLink(2, 8);
	G.addLink(2, 6);
	G.addLink(6, 7);
	G.addLink(6, 8);
	G.sortList();
	cout << " Depth First Search " << endl;
	G.dfs();
	cout << " Breadth First Search " << endl;
	G.bfs();
}



void runSearch() {
	//runBinarySearchTree();
	runDepthFirstSearch();
}