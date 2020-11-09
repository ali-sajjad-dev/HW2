#include <iostream>
#include "Stack.h";
#include "moveNode.h"

using namespace std;

// Stack specially designed for moves in a path


// add new move coordinate node to the top of the stack
template<typename T>
void Stack<T>::push(T x, T y)
{
	// add first
	if (size == 0)
	{
		top = new MoveNode<T>(x, y);
		bottom = top;
		size++;
	}
	else
	{
		// add new node to top
		MoveNode<T>* tmp = new MoveNode<T>(x, y);
		tmp->next = top;
		top = tmp;
		size++;
	}
}

// remove a moveNode from atop the stack
template<typename T>
void Stack<T>::pop()
{
	if (size == 0)
	{
		cout << "Cannot pop off an empty stack" << endl;
		return;
	}
	else
	{
		MoveNode<T>* tmp;
		tmp = top->next;
		delete top;
		top = tmp;
		size--;
	}
}

template<typename T>
void Stack<T>::print_Stack_path()
{
	MoveNode<T>* tmp = top;

	cout << "END";
	while (tmp != nullptr)
	{
		cout << " <- ";
		cout << "(" << tmp->move[0] << ", " << tmp->move[1] << ")";
		tmp = tmp->next;
	}
	cout << " START" << endl;
}


template<typename T>
void Stack<T>::insert(int index, T x, T y)
{
	// ensure valid index
	if (index < 0 || index > size - 1)
	{
		cout << "Invalid index" << endl;
		return;
	}
	else if (index == 0)
	{
		push(x, y);
	}
	else
	{
		MoveNode<T>* tmp = top;
		for (int i = 0; i < index - 1; i++)
		{
			tmp = tmp->next;
		}
		// create new node w/ new data input
		MoveNode<T>* new_node = new MoveNode<T>(x,y);

		// point new node to what previous node references
		new_node->next = tmp->next;

		// point previous node to new_node
		tmp->next = new_node;
	}
}


// check if move is legal
template<typename T>
bool Stack<T>::isLegal(T maze[][5], int row, int col)
{
	// returns false if path is obstructed
	if (row > 4 || col > 4)
	{
		return false;
	}
	else if (maze[row][col] == 1)
	{
		return true;
	}
	return false;
}


// solve the maze
template<typename T>
void Stack<T>::solveMaze(T maze[][5], int row, int col)
{
	// true for down, false for across
	bool step_taken = true;

	// start postion
	push(row, col);

	//pointer to current position in stack
	MoveNode<int>* current_pos = top;

	// pointer to destination coordinates
	MoveNode<int>* END = new MoveNode<int>(4, 4);

	// continue until END position is reached
	while (!current_pos->compare(*END))
	{
		int next_row = row + 1;
		int next_col = col + 1;

		if (isLegal(maze, next_row, col))
		{
			row++;
			push(row, col);
			current_pos = top;
			step_taken = true;
		}
		else if (isLegal(maze, row, next_col))
		{
			col++;
			push(row, col);
			current_pos = top;
			step_taken = false;
		}
		else
		{   // backtrack

			// remove current step
			pop();

			if (step_taken)
			{
				// take alternative
				if (isLegal(maze, row - 1, col + 1))
					push(--row, ++col);
				current_pos = top;
				row = current_pos->move[0];
				col = current_pos->move[1];
			}
			else
			{
				// take alternative
				if (isLegal(maze, row + 1, col + 1))
					push(++row, --col);
				current_pos = top;
				row = current_pos->move[0];
				col = current_pos->move[1];
			}
		}
	}
}