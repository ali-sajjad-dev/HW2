#pragma once

using namespace std;

// generic node for each move
template<typename T>
class MoveNode
{
public:
	// each move corresponds to a grid coordinate
	// hence a 1D array of 2 elements
	T move[2];
	// pointer to next node
	MoveNode* next;
	
	// node constructor
	template<typename T>
	MoveNode(T x, T y)
	{
		move[0] = x;
		move[1] = y;
		next = nullptr;
	}
	
	// compare two nodes, i.e. 2 coordinates 
	bool compare(MoveNode a);
};

