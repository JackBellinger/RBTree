#include "RBTree.h"
#include "Heap.h"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <cstddef>
#include <cmath>
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

void generateForwardSorted(int* array, double length)
{

	for(int i = 0; i < length; i++)
	{
		array[i] = i;
	}
}

void generateBackwardSorted(int* array, double length)
{

	for(int i = 0; i < length; i++)
	{
		array[i] = length - 1 - i;
	}
}
void generateRandomSorted(int* array, double length)
{
	generateForwardSorted(array, length);
	Heap<int> heap(length);
	heap.heapSortRandomizer(array, length);
}
void generateRBTreeSorted(int* array, double length)
{
	RBTree<int> tree();
	for(int i = 0; i < length; i++)
	{
		//tree.insert(
	}
}
void printArray(double* array, double length)
{
	for(int i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}
void printArray(int* array, double length)
{
	for(int i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}
void printVector(vector<double> vector)
{
	for(double d : vector)
		cout << d << " ";
	cout << endl;
}
bool validateAscendingSort(int* array, double length)
{//checks if every element is greater than the previous
	for(int i = 1; i < length; i++)
		if(array[i - 1] > array[i])
		{	
			cout << array[i-1] << " > " << array[i] << endl;
			return false;
		}
	return true;
}
double timeBasicSorts(size_t (*sortingAlgo)(int*, double), int* array, double length)
{
	// The "auto" type determines the correct type at compile-time
	auto startT = std::chrono::system_clock::now();

	size_t swaps = sortingAlgo(array, length);

	auto endT = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = endT-startT;
	double time = elapsed_seconds.count();
	std::time_t end_time = std::chrono::system_clock::to_time_t(endT);

	//cout << "finished at " << std::ctime(&end_time) 
	//     << "elapsed time: " << time << " s"
	//     << "\nNumber of swaps: " << swaps << "\n";
	//double checks that the array is sorted correctly
	if(validateAscendingSort(array, length))
		cout << "Array is Sorted Correctly" << endl;
	else
		cout << "Array is not Sorted Correctly" << endl;
	return time;
}

double timeRecursiveSorts( size_t (*sort) (int*, size_t, size_t), int* array, size_t start, size_t end)
{
	// The "auto" type determines the correct type at compile-time
	auto startT = std::chrono::system_clock::now();

	size_t swaps = sort(array, start, end);

	auto endT = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = endT-startT;
	double time = elapsed_seconds.count();
	std::time_t end_time = std::chrono::system_clock::to_time_t(endT);

	/*cout << "finished at " << std::ctime(&end_time) 
	  << "elapsed time: " << time << " s"
	  << "\nNumber of swaps: " << swaps << "\n";
	//double checks that the array is sorted correctly
	if(validateAscendingSort(array, end))
	cout << "Array is Sorted Correctly" << endl;
	else
	cout << "Array is not Sorted Correctly" << endl;
	 */
	return time;
}
double timeHeapSort(int* array, int size)
{
	Heap<int> heap(size);
	auto startT = std::chrono::system_clock::now();

	heap.heapSort(array, size);

	auto endT = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = endT-startT;
	double time = elapsed_seconds.count();
	std::time_t end_time = std::chrono::system_clock::to_time_t(endT);

	return time;
}
enum rbtOperation
{
	insert = 0,
	find = 1,
	delet = 2
};
double timeRBTree(RBTree<int>* tree, int op, int value)
{
	auto startT = std::chrono::system_clock::now();
	switch(op)
	{
		case 0://::insert:
			tree->rbtInsert(value);
			break;
		case 1://::find:
			tree->rbtSearch(value);
			break;
		case 2://::delet:
			tree->rbtDelete(value);
	}
	auto endT = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = endT-startT;
	double time = elapsed_seconds.count();
	std::time_t end_time = std::chrono::system_clock::to_time_t(endT);

}
int lab7()
{

	string opNames[3] = {"Insertion", "Searching", "Deletion"};

	vector<vector<double>> opTimesWorst(3, vector<double>(10, 0));
	vector<vector<double>> opTimesAvg(3, vector<double>(10, 0));
	vector<double> sizes(10, 0);
	cout << "size: " <<sizes[0] << endl;
	int numSizes = 0;//counter not a constant
	int numSamples = 10;

	void(*generators[3])(int*, double);
	generators[0] = generateForwardSorted;
	generators[1] = generateRandomSorted;
	//generators[2] = generateRBTreeSorted;

	for(int g = 0; g < 2; g++)//generators = best / worst case loop
	for(int SIZE = 1000; SIZE <= 10000; SIZE += 1000)
	{
		
		sizes[numSizes] = (double)SIZE;
		for(int x = 0; x < numSamples; x++)
		{
			RBTree<int>* tree = new RBTree<int>();
			int elements[SIZE];
			generators[g](elements, SIZE);
			for(int op = 0; op < 3; op++)
				for(int i = 0; i < SIZE; i++)
				{
					double time = timeRBTree(tree, op, elements[i]);
					if(g == 0)
						opTimesWorst[op][numSizes] += time;
					if(g == 1)
						opTimesAvg[op][numSizes] += time;
				}
			tree->cleanNodes();
			delete tree;
		}//samples loop

		for(int op = 0; op < 3; op++)
		{
			if(g == 0)
				opTimesWorst[op][numSizes] = opTimesWorst[op][numSizes] / numSamples;
			if(g == 1)
				opTimesAvg[op][numSizes] = opTimesAvg[op][numSizes] / numSamples;
			//cout << "Average time to 
		}
		numSizes++;
	}//size loop
	double c1 = 0.00001;
	vector<double> nlogn(10, 0);

	double c2 = 0.00000012;
	vector<double> n2(10, 0);

	for(int i = 0; i < 10; i++)
	{
		nlogn[i] = c1 * sizes[i] * log(sizes[i]);
		n2[i] = c2 * pow(sizes[i], 2);
	}
	cout << "sizes: "; printVector(sizes);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < numSizes; j++)
		{
			
		}
		cout << "Worst Cases:\n" << opNames[i] << ": ";
		printVector(opTimesWorst[i]);
		
		cout << "Best Cases:\n" << opNames[i] << ": ";
		printVector(opTimesAvg[i]);

	}
	
	plt::figure_size(1200, 780);
	plt::named_plot("nlog(n)", sizes, nlogn);
	plt::named_plot("n^2", sizes, n2);
	
	for(int i = 0; i < 3; i++)
	{
		plt::named_plot("Worst Case " + opNames[i], sizes, opTimesWorst[i]);
		plt::named_plot("Average Case " + opNames[i], sizes, opTimesAvg[i]);
	}
	plt::xlim(0, 10000);
	plt::title("RBTree Operations Timing");
	plt::legend();
	plt::save("./plot.png");
	return 1;
}
int main()
{
	lab7();
}

