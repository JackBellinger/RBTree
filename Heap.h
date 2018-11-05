#ifndef HEAP_H
#define HEAP_H
template<class T>
class pQNode
{
public:
	int key = -1;
	T data;
	pQNode();
	pQNode(int);
	pQNode(T, int);
};


template <class T>
class Heap
{
public:
	pQNode<T>* data;
	int size;
	int arraySize;
	
	int leftChild(int);
	int rightChild(int);
	int parent(int);
	void swap(int, int);
	

	Heap(int = 100);
	
	void heapSort(T*, int);
	void buildHeapRandomizer(T*, int);
	void buildHeap(T*, int);
	void heapify(int);
	void increaseSize(int);
	
	void peek();
	T extractMax();
	
	void insert(pQNode<T>);
	void insert();

	void printHeap();
	
	void heapSortRandomizer(T*, int);
	
	pQNode<T> operator [](int);
private:
	void increaseKey();
};


#endif
