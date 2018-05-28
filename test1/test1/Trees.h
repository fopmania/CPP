#pragma once

class MinHeap
{
	int *harr = NULL; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
public:
	// Constructor
	MinHeap(int capacity);
	~MinHeap() { if (harr != NULL)	delete harr; }

	void MinHeapify(int);

	int parent(int i) { return (i - 1) / 2; }

	int left(int i) { return (2 * i + 1); }

	int right(int i) { return (2 * i + 2); }

	int extractMin();

	void decreaseKey(int i, int new_val);

	int getMin() { return harr[0]; }

	void deleteKey(int i);

	void insertKey(int k);
};
void run_tree();


