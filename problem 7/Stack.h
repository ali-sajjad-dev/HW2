#pragma once
#include "moveNode.h"

using namespace std;

template <class T>
class Stack
{
public:
	MoveNode<T>* top;
	MoveNode<T>* bottom;
	int size;

	// constructor
	Stack()
	{
		top = nullptr;
		bottom = nullptr;
		size = 0;
	}

	void push(T x, T y);

	void pop();

	void insert(int index, T x, T y);

	void print_Stack_path();

	bool isLegal(T maze[][5], int row, int col);

	void solveMaze(T maze[][5], int row, int col);

};
