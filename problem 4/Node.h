#pragma once

// generic node
template <typename T>
class Node
{
public:
	// data in node of type T
	T data;
	// pointer to the next node
	Node<T>* next;
	
	// default constructor
	Node()
	{
		this->data = -1;
		this->next = nullptr;
	}
	
	// constructor w/ data input
	Node(T data)
	{
		this->data = data;
		this->next = nullptr;
	}
};

