#include "Heap.h"
#include <cmath>

template <class T>
pQNode<T>::pQNode()
{
	//key = -1;	
}
template <class T>
pQNode<T>::pQNode(T d, int k)
{
	data = d;
	key = k;
}
template <class T>
pQNode<T>::pQNode(int select)
{
	
}
template <>
pQNode<int>::pQNode(int select)
{
	cout << "Enter a value for the node: ";
	cin >> data;

}
template <class T>
Heap<T>::Heap(int s)
{
	arraySize = s;
	size = 0;
	data = new pQNode<T>[arraySize];
}
template <class T>
void Heap<T>::heapSort(T* array, int size)
{
	buildHeap(array, size);
	for(int i = 0; i < size; i++)
		array[i] = extractMax();
}
template <class T>
pQNode<T> Heap<T>::operator [](int i)
{
	return data[i];
}
template <class T>
void Heap<T>::insert()
{
	cout << "size: " << size << " heap size: " << arraySize << endl;
	pQNode<T> n = pQNode<T>(1);
	cout << "Priority? : ";
	cin >> n.key;
	insert(n);	
}
template <class T>
void Heap<T>::insert(pQNode<T> newNode)
{
	//insert the new element at the bottom and move it up until it's in the right spot
	increaseSize(size+1);
	int i = size;
	while(i > 0 && data[parent(i)].key < newNode.key)
	{
		data[i] = data[parent(i)];
		i = parent(i);
	}
	data[i] = newNode;
	size++;
}
template <class T>
void Heap<T>::peek()
{
	cout << " Max: " << data[0].data;
}
template <class T>
T Heap<T>::extractMax()
{
	if(size < 1)
		throw "error: heap underflow";
	else
	{
		T max = data[0].data;
		data[0] = data[size - 1];
		size--;
		heapify(0);
		return max;
	}
}
template <class T>
void Heap<T>::buildHeap(T* A, int s)
{
	size = s;
	arraySize = size +1;
	for(int i = (size/2)-1; i >= 0; i--)  //start at the last internal node
		heapify(i);
}
template <class T>
void Heap<T>::buildHeapRandomizer(T* A, int s)
{//this function is not the regular build heap!
 //since this is a priority queue, build Heap is only used for the bonus array randomizer
	pQNode<T>* temp = data;
	size = s;//size is #elements, ie indexed to 1
	arraySize = size +1;
	data = new pQNode<T>[arraySize];
	for(int i = 0; i < arraySize; i++)
		data[i] = pQNode<T>(A[i], rand() % size*size*size);
	for(int i = (size/2)-1; i >= 0; i--)  //heapify from the last internal node
		heapify(i);
}

template <class T>
void Heap<T>::heapSortRandomizer(T* array, int size)
{
	buildHeapRandomizer(array, size);
	for(int i = 0; i < size; i++)
		array[i] = extractMax();
}

template <class T>
void Heap<T>::heapify(int i)
{
	int L = leftChild(i);
	int R = rightChild(i);
	int largest = i;
	if(i >= size)
		return;
	//cout << data[i];
	//cout << data[L];
	if( L < size && data[i].key < data[L].key)
		largest = L;
	else
		largest = i;
	if( R < size && data[largest].key < data[R].key)
		largest = R;

	if(largest != i)
	{
		swap(i, largest);
		heapify(largest);
	} 
}
template <class T>
void Heap<T>::increaseSize(int requestedSize)
{//add layers to the heap until the requested size fits into the array
	int newSize = 2;
	while(requestedSize > newSize)
		newSize *= 2;
	if(newSize > arraySize)
	{
		cout << "increasing size to " << newSize << endl;
		pQNode<T>* newData = new pQNode<T>[newSize];
		int i;
		for(i = 0; i < size; i++)
			newData[i] = data[i];
		size = requestedSize;
		arraySize = newSize;
		
		pQNode<T>* temp = data;
		data = newData;
		newData = temp;
		delete newData;
	}
	
}
template <class T>
int Heap<T>::leftChild(int i)
{
	return (2*i+ 1);
}
template <class T>
int Heap<T>::rightChild(int i)
{
	return 2*i+2;
}
template <class T>
int Heap<T>::parent(int i)
{
	if(i%2 == 0)
		return (i-1)/2;
	else
		return i/2;
}
template <class T>
void Heap<T>::swap(int x, int y)
{
	pQNode<T> temp = data[x];
	data[x] = data[y];
	data[y] = temp;
}
bool isPow2(int x)
{
	return x > 0 && !(x & (x-1));
}
template <class T>
void Heap<T>::printHeap()
{
	//int height = log2(size);
	int nextEndl = 2;
	int offset = 2;
	for(int i = 0; i < size; i++)
	{
		if(i+1 == nextEndl)
		{//if the main loop gets to an element that should be on a new line, cout endl
			cout << endl;
			nextEndl *= 2;
		}
		if(data[i].key != -1)
			cout << data[i].key << ": " << data[i].data;
		else
			cout << "XXX";
		
		//used to dynamically set the space between the elements
		for(int o = 0; o < offset; o++)
			cout << " ";
	}
		cout << endl << endl;
}
