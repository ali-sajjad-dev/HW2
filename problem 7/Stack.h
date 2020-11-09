#pragma once
#include "moveNode.h"

using namespace std;

// generic stack class
template <class T>
class Stack
{
public:
	// data members
	// pointers and size of stack
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
	
	// add a new element to top
	void push(T x, T y);

	// remove top most element
	void pop();

	// insert element at given index
	void insert(int index, T x, T y);

	// print out the entire maze path
	void print_Stack_path();

	// check to see if a move is legal
	bool isLegal(T maze[][5], int row, int col);
	
	// solve the given maze
	void solveMaze(T maze[][5], int row, int col);

};
