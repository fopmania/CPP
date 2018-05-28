#include "stdafx.h"
#include "linkedlist.h"
#include <iostream>

using namespace std;

typedef struct stNode {
	int data;
	struct stNode *next = NULL;
};
void segregateEvenOdd(stNode **head_ref)
{
	stNode *end = *head_ref;
	stNode *prev = NULL;
	stNode *curr = *head_ref;

	while (end->next != NULL)
		end = end->next;

	stNode *new_end = end;

	while (curr->data % 2 != 0 && curr != end)
	{
		new_end->next = curr;
		curr = curr->next;
		new_end->next->next = NULL;
		new_end = new_end->next;
	}

	if (curr->data % 2 == 0)
	{
		*head_ref = curr;
		while (curr != end)
		{
			if ((curr->data) % 2 == 0)
			{
				prev = curr;
				curr = curr->next;
			}
			else
			{
				prev->next = curr->next;
				curr->next = NULL;
				new_end->next = curr;
				new_end = curr;
				curr = prev->next;
			}
		}
	}
	else prev = curr;

	if (new_end != end && (end->data) % 2 != 0)
	{
		prev->next = end->next;
		end->next = NULL;
		new_end->next = end;
	}
	return;
}
void pushNodeBegin(stNode** head_ref, int new_data)
{
	stNode* new_node = new stNode();

	new_node->data = new_data;

	new_node->next = (*head_ref);

	(*head_ref) = new_node;
}

void pushNodeEnd(stNode** head_ref, int new_data)
{
	stNode* new_node = new stNode();
	stNode* end = *head_ref;
	new_node->data = new_data;
	new_node->next = NULL;

	if (*head_ref == NULL) {
		*head_ref = new_node;
	}
	else {
		while (end->next != NULL) {
			end = end->next;
		}
		end->next = new_node;
	}


}

/* Function to print nodes in a given linked list */
void printList(stNode *node)
{
	while (node != NULL)
	{
		printf("%d ", node->data);
		node = node->next;
	}
}

int Segregate_even_and_odd() {
	stNode *arrHead[100];
	int T, N, V;
	do {
		scanf("%d", &T);
	} while (T < 1 || T > 80);

	for (int i = 0; i < T; i++) {
		stNode *head = NULL;
		do {
			scanf("%d", &N);
		} while (N < 1 || N > 100);

		
		for(int k = 0; k < N; k++)
		{
			do {
				scanf("%d", &V);
			} while (V < 1 || V > 1000);
			pushNodeEnd(&head, V);
		}
		segregateEvenOdd(&head);
		arrHead[i] = head;
	}

	for (int c = 0; c < T; c++) {
		printList(arrHead[c]);
	}
	//code
	return 0;
}

void push(stNode **head_ref, int new_data) {
	stNode *new_node = new stNode();
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;

}

void pushEnd(stNode **head_ref, int new_data) {
	stNode *cur = *head_ref;
	stNode *new_node = new stNode();
	new_node->data = new_data;

	if (cur == NULL) {
		*head_ref = new_node;
	}
	else {
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = new_node;
	}
}


int countNodes(stNode *s)
{
	int count = 0;
	while (s != NULL)
	{
		count++;
		s = s->next;
	}
	return count;
}


void swapNodes(stNode **head_ref, int x, int y)
{
	if (x == y) return;

	stNode *prevX = NULL, *currX = *head_ref;
	while (currX && currX->data != x)
	{
		prevX = currX;
		currX = currX->next;
	}

	stNode *prevY = NULL, *currY = *head_ref;
	while (currY && currY->data != y)
	{
		prevY = currY;
		currY = currY->next;
	}

	if (currX == NULL || currY == NULL)
		return;

	if (prevX != NULL)
		prevX->next = currY;
	else 
		*head_ref = currY;

	if (prevY != NULL)
		prevY->next = currX;
	else 
		*head_ref = currX;

	stNode *temp = currY->next;
	currY->next = currX->next;
	currX->next = temp;
}
/*
void swapNodes(stNode **head_ref, stNode *n1, stNode *n2) {
	stNode *p1 = NULL, *p2 = NULL, *cur = *head_ref;
	stNode *next1 = n1->next;
	stNode *next2 = n2->next;


	while (cur->next != NULL) {
		if (p1 == NULL || n2 == NULL) {
			if (cur->next == n1)		p1 = cur;
			if (cur->next == n2)		p2 = cur;
		}
		else break;

		cur = cur->next;
	};

	if (p1 != NULL) {
		p1->next = n2;
	}
	if (p2 != NULL) {
		p2->next = n1;
	}
	n1->next = next2;
	n2->next = next1;
}
*/

bool swapKth(stNode **head_ref, int k)
{
	int size = countNodes(*head_ref);
	if (2 * k > size) {
		return false;
	}

	stNode *cur = *head_ref, *n1 = NULL, *n2 = NULL;
	int i1 = k, i2 = size - k + 1, count = 1;

	while (cur != NULL)
	{
		if (n1 == NULL || n2 == NULL) {
			if (i1 == count)		n1 = cur;
			if (i2 == count)		n2 = cur;
		}
		else break;

		cur = cur->next;
		count++;
	}
	swap(n1->data, n2->data);
	return true;
}

void run_swapping_kth_nodes() {
	stNode *head = NULL;
	for (int i = 1; i < 9; i++)
		pushEnd(&head, i);

	cout << "Original Linked List: ";
	printList(head);

	for (int k = 1; k < 9; k++)
	{
		cout << "\nModified List for k = " << k << endl;
		if (swapKth(&head, k)) {
			printList(head);
		}else	cout << "LIST IS OF LESSER SIZE" << endl;
	}

}