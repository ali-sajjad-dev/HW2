#pragma once
#include "Node.h"

// generic stack of type T
template <typename T>
class Stack
{
public:
	// data members
	// pointers to nodes and size
	Node<T>* top;
	Node<T>* bottom;
	int size;

	// constructor
	Stack()
	{
		top = nullptr;
		bottom = nullptr;
		size = 0;
	}
	
	// add data to top of stack
	void push(T data);

	// remove top most node
	void pop();
	
	// insert data to specified index
	void insert(int index, T type);
	
	// print out contents of stack to console
	void printStack();
};
