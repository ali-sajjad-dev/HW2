#include <iostream>
#include "Stack.h"
#include "moveNode.h"
#include "Stack.cpp"

using namespace std;

// create an arbitrary maze

int main() {
	
	// maze, 1s are legal, 0s are impassable terrain
	int maze[5][5] = {

		{1, 0, 0, 0, 0},
		{1, 1, 1, 0, 0},
		{1, 0, 1, 1, 1},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 1, 1}
	};

	// path stack of moves
	Stack<int> path;

	// row and column
	int row = 0;
	int col = 0;

	// solve maze
	path.solveMaze(maze, row, col);
	
	// print completed path
	path.print_Stack_path();
}

// custom comparator, determine whether 2 nodes i.e. coordinates are the same spot in the maze
template <typename T>
bool MoveNode<T>::compare(MoveNode x)
{
	// compare class object to another object
	if (move[0] == x.move[0] && move[1] == x.move[1])
	{
		return true;
	}
	return false;
}
