#include "stdafx.h"
#include "Trees.h"
#include <iostream>

using namespace std;

void swap(int *x, int *y);
/*{
	int temp = *x;
	*x = *y;
	*y = temp;
}*/


// Heap Tree
MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	int root = harr[0];
	harr[0] = harr[heap_size - 1];
	heap_size--;
	MinHeapify(0);

	return root;
}


void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

//============================================================
typedef struct binNode
{
	int value;
	binNode *left, *right;
};

binNode *newBinNode(int val)
{
	binNode *temp = new binNode();
	temp->value = val;
	temp->left = temp->right = NULL;
	return temp;
}

void orderBinTree(binNode *root)
{
	if (root != NULL)
	{
		orderBinTree(root->left);
		printf("%d \n", root->value);
		orderBinTree(root->right);
	}
}

binNode* insertBinTree(binNode* node, int value)
{
	if (node == NULL) return newBinNode(value);

	if (value < node->value)
		node->left = insertBinTree(node->left, value);
	else if (value > node->value)
		node->right = insertBinTree(node->right, value);

	return node;
}

//============================================================

void run_tree()
{
	cout << "heap tree order" << endl;
	// heap tree
	MinHeap h(11);
	h.insertKey(3);
	h.insertKey(2);
	h.insertKey(1);
	//h.deleteKey(1);
	h.insertKey(15);
	h.insertKey(5);
	h.insertKey(4);
	h.insertKey(45);
	//cout << h.extractMin() << " ";
	cout << "getMin : " << h.getMin() << " ";
	//h.decreaseKey(2, 1);
	//cout << h.getMin();

	//	binary tree

	cout << "\nbinary tree order" << endl;
	binNode *root = newBinNode(50);
	insertBinTree(root, 30);
	insertBinTree(root, 20);
	insertBinTree(root, 40);
	insertBinTree(root, 70);
	insertBinTree(root, 60);
	insertBinTree(root, 80);

	orderBinTree(root);
}
