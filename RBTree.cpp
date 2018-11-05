//#include "TNode.h"
#include "RBTree.h"
#include "Student.h"
#include <iostream>
using namespace std;

	template <class DT>
TNode<DT>::TNode(DT* d)
{
	parent = RBTree<DT>::nil;
	left = RBTree<DT>::nil;
	right = RBTree<DT>::nil;
	data = *d;
}
	template <class DT>
TNode<DT>::TNode(DT d)
{
	parent = RBTree<DT>::nil;
	left = RBTree<DT>::nil;
	right = RBTree<DT>::nil;
	data = d;
}
	template <class DT>
TNode<DT>::TNode(DT d, color_t c)
{
	parent = RBTree<DT>::nil;
	left = RBTree<DT>::nil;
	right = RBTree<DT>::nil;
	data = d;
	color = c;
}
	template <class DT>
RBTree<DT>::RBTree()
{
	root = RBTree<DT>::nil;
}

	template <class DT>
RBTree<DT>::~RBTree()
{
	cleanNodes();
}

	template <class DT>
TNode<DT>* RBTree<DT>::createNode()
{
	DT* data = new DT();
	TNode<DT>* newNode = new TNode<DT>(data);
	return newNode;
}
	template <>
TNode<int>* RBTree<int>::createNode()
{
	int* data = new int();
	cout << "What would you like to insert?" << endl;
	cin >> *data;
	TNode<int>* newNode = new TNode<int>(data);
	return newNode;
}
	template <>
TNode<Student>* RBTree<Student>::createNode()
{
	Student* data = new Student();
	data->inputData();
	TNode<Student>* newNode = new TNode<Student>(data);
	return newNode;
}
	template <class DT>
bool RBTree<DT>::rbtInsert()
{
	return rbtInsert(createNode());
}
	template <class DT>
bool RBTree<DT>::rbtInsert(DT data)
{
	TNode<DT>* node = new TNode<DT>(data);
	return rbtInsert(node);
}
	template <class DT>
bool RBTree<DT>::rbtInsert(TNode<DT>* newNode)
	//returns true if the node was added successfully, false if it couldn't add it
{
	if(root == RBTree<DT>::nil)
	{
		root = newNode;
		return true;
	}
	else
	{
		TNode<DT>* current = root;
		TNode<DT>* prev = root;
		while(current)
		{
			prev = current;
			if(newNode->data <= current->data)
				current = current->left;
			else if(newNode->data > current->data)
				current = current->right;
		}//end while
		if(newNode->data <= prev->data)
			prev->left = newNode;
		else if(newNode->data > prev->data)
			prev->right = newNode;
		newNode->parent = prev;
	}
	return false;//the function should never get to this statement, only if theres an error
}
	template <class DT>
void RBTree<DT>::rbtDelete(DT data)
{
	rbtDelete(rbtSearch(data));
}
	template <class DT>
void RBTree<DT>::rbtDelete(TNode<DT>* node)
{
	if(node == RBTree<DT>::nil)
		cout << "Couldn't delete" << endl;
	else
	{
		TNode<DT>* del = node;
		TNode<DT>* replace = node;
		if(node->left == RBTree<DT>::nil || node->right == RBTree<DT>::nil)
			del = node;
		else
			del = successor(node);
		if(del->left != RBTree<DT>::nil)
			replace = del->left;
		else
			replace = del->right;
		transplant(del, replace);
		//if the node to be deleted is a leaf del will = replace
		if( del != replace)
			node->data = del->data;
		delete del;
	}
}

	template <class DT>
TNode<DT>* RBTree<DT>::rbtSearch(DT data)
{
	TNode<DT>* current = root;
	while(current != RBTree<DT>::nil)
	{
		if(current->data == data)
		{
			//cout << "found" <<endl;
			return current;
		}
		if(data <= current->data)// && current->left != RBTree<DT>::nil)
			current = current->left;
		else if(data > current->data)// && current->right != RBTree<DT>::nil)
			current = current->right;
	}
	cout << "node not found" << endl;
	return RBTree<DT>::nil;//if the loop exits without returning that means the data it's 	looking for isn't in the tree
}

	template <class DT>
void RBTree<DT>::cleanNodes()
{
	cleanNodes(root);
}

	template <class DT>
void RBTree<DT>::cleanNodes(TNode<DT>* x)
{
	if(x != RBTree<DT>::nil)
	{
		cleanNodes(x->left);
		cleanNodes(x->right);
		delete x;
	}
}

	template <class DT>
TNode<DT>* RBTree<DT>::max()
{
	max(root);
}

	template <class DT>
TNode<DT>* RBTree<DT>::max(TNode<DT>* max)
{
	if(max != RBTree<DT>::nil)
		while(max->right != RBTree<DT>::nil)
		{
			max = max->right;
		}
	return max;
}

	template <class DT>
TNode<DT>* RBTree<DT>::min()
{
	min(root);
}

	template <class DT>
TNode<DT>* RBTree<DT>::min(TNode<DT>* min)
{
	if(min != RBTree<DT>::nil)	
		while(min->left != RBTree<DT>::nil)
		{
			min = min->left;
		}
	return min;
}

	template <class DT>
TNode<DT>* RBTree<DT>::successor()
{
	successor(root);
}

	template <class DT>
TNode<DT>* RBTree<DT>::successor(TNode<DT>* current)
{
	return min(current->right);
}

	template <class DT>
TNode<DT>* RBTree<DT>::predecessor()
{
	predecessor(root);
}

	template <class DT>
TNode<DT>* RBTree<DT>::predecessor(TNode<DT>* current)
{
	return max(current->left);
}
	template <class DT>
void RBTree<DT>::transplant(TNode<DT>* del, TNode<DT>* replace)
{
	if(replace != RBTree<DT>::nil)
		replace->parent = del->parent;
	if(del->parent == RBTree<DT>::nil)
		root = replace;
	else if(del == del->parent->left)
		del->parent->left = replace;
	else
		del->parent->right = replace; 
}
	template <class DT>
void RBTree<DT>::lRotate(TNode<DT>* x)
{
	TNode<DT>* y =  x->right;
	x->right = y->left;
	if(y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;
	if(x->parent != nil)
		if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	else
		root = y;
	y->left = x;
	x->parent = y;
}
	template <class DT>
void RBTree<DT>::rRotate(TNode<DT>* x)
{
	TNode<DT>* y =  x->left;
	x->left = y->right;
	if(y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;
	if(x->parent != nil)
		if(x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	else
		root = y;
	y->right = x;

}
	template <class DT>
void RBTree<DT>::inOrder()
{
	inOrder(root);
}

	template <class DT>
void RBTree<DT>::inOrder(TNode<DT>* current)
{
	if(current != RBTree<DT>::nil)
	{
		inOrder(current->left);
		cout << current->data << ", ";
		inOrder(current->right);
	}
}

	template <class DT>
void RBTree<DT>::preOrder()
{
	preOrder(root);
}

	template <class DT>
void RBTree<DT>::preOrder(TNode<DT>* current)
{
	if(current != RBTree<DT>::nil)
	{
		cout << current->data << ", ";
		preOrder(current->left);
		preOrder(current->right);
	}
}

	template <class DT>
void RBTree<DT>::postOrder()
{
	postOrder(root);
}

	template <class DT>
void RBTree<DT>::postOrder(TNode<DT>* current)
{
	if(current != RBTree<DT>::nil)
	{
		postOrder(current->left);
		postOrder(current->right);
		cout << current->data << ", ";
	}
}

	template <class DT>
DT* RBTree<DT>::rbtToArray(DT* array, int index, TNode<DT>* current)
{

	//	if(current != RBTree<DT>::nil)
	//	{
	//		array[index] = current;
	//		rbtToArray(array, index/2, current->left);
	//		rbtToArray(array, index + index/2, current->right);
	//	}
}
