#include "TNode.h"
#include <iostream>
using namespace std;

template <class DT>
TNode<DT>::TNode(DT* d)
{
	parent = NULL;
	left = NULL;
	right = NULL;
	data = *d;
}

template <class DT>
TNode<DT>::TNode(DT d)
{
	parent = NULL;
	left = NULL;
	right = NULL;
	data = *d;
}
//class template TNode<int>;
//class template TNode<Student>;
