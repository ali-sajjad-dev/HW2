#pragma once

using namespace std;

template<typename T>
class MoveNode
{
public:
	T move[2];
	MoveNode* next;

	template<typename T>
	MoveNode(T x, T y)
	{
		move[0] = x;
		move[1] = y;
		next = nullptr;
	}

	bool compare(MoveNode a);
};

