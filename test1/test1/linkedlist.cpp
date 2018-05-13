#include "stdafx.h"
#include "linkedlist.h"


struct Node {
	int data;
	struct Node *next;
};
void segregateEvenOdd(struct Node **head_ref)
{
	struct Node *end = *head_ref;
	struct Node *prev = NULL;
	struct Node *curr = *head_ref;

	while (end->next != NULL)
		end = end->next;

	struct Node *new_end = end;

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
void pushNodeBegin(struct Node** head_ref, int new_data)
{
	struct Node* new_node = new Node;

	new_node->data = new_data;

	new_node->next = (*head_ref);

	(*head_ref) = new_node;
}

void pushNodeEnd(struct Node** head_ref, int new_data)
{
	struct Node* new_node = new Node;
	struct Node* end = *head_ref;
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
void printList(struct Node *node)
{
	while (node != NULL)
	{
		printf("%d ", node->data);
		node = node->next;
	}
}

int Segregate_even_and_odd() {
	struct Node *arrHead[100];
	int T, N, V;
	do {
		scanf("%d", &T);
	} while (T < 1 || T > 80);

	for (int i = 0; i < T; i++) {
		struct Node *head = NULL;
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
