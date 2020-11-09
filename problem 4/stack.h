#pragma once
#include "Node.h"

template <typename T>
class Stack
{
public:
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

	void push(T data);

	void pop();

	void insert(int index, T type);

	void printStack();
};
