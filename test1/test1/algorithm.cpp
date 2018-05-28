#include "stdafx.h"



int tdata[10]; //nPr을 이루는 각각의 경우를 저장
int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

void swap(int *i, int *j) {
	int temp = *i;
	*i = *j;
	*j = temp;
}
void print_result(int q) {
	for (int i = q - 1; i >= 0; i--) {
		printf("%d ", tdata[i]);
	}
	printf("\n");
}

void permutation(int n, int s, int q)
{
	if (s == 0) {
		print_result(q);
		return;
	}

	for (int i = n - 1; i >= 0; i--) {
		swap(&data[i], &data[n - 1]);
		tdata[s - 1] = data[n - 1];
		permutation(n - 1, s - 1, q);
		swap(&data[i], &data[n - 1]);
	}
}



void Combination(int n, int s, int q) {
	if (s == 0) {
		print_result(q);
		return;
	}
	else if (n<s) {
		return;
	}
	else {
		tdata[s - 1] = data[n - 1];
		Combination(n - 1, s - 1, q);  //n-1Cr-1: 
		Combination(n - 1, s, q);    //n-1Cr:
	}
}

// 중복 조합
void comb(int n, int s, int q)
{
	int i;
	if (s == q) {
		print_result(q);
		return;
	}

	for (i = 0; i < n; i++) {
		tdata[s] = data[i];
		comb(n, s + 1, q);
	}
}


typedef struct node
{
	int data;
	struct node* left;
	struct node* right;
};

/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
struct node* newNode(int data)
{
	struct node* node = (struct node*)
		 new char(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return(node);
}

/* Given a binary tree, print its nodes according to the
"bottom-up" postorder traversal. */
void printPostorder(struct node* node)
{
	if (node == NULL)
		return;

	// first recur on left subtree
	printPostorder(node->left);

	// then recur on right subtree
	printPostorder(node->right);

	// now deal with the node
	printf("%d ", node->data);
}

/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct node* node)
{
	if (node == NULL)
		return;

	/* first recur on left child */
	printInorder(node->left);

	/* then print the data of node */
	printf("%d ", node->data);

	/* now recur on right child */
	printInorder(node->right);
}

/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct node* node)
{
	if (node == NULL)
		return;

	/* first print data of node */
	printf("%d ", node->data);

	/* then recur on left sutree */
	printPreorder(node->left);

	/* now recur on right subtree */
	printPreorder(node->right);
}

