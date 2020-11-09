#pragma once

// generic node
template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;

	Node()
	{
		this->data = -1;
		this->next = nullptr;
	}

	Node(T data)
	{
		this->data = data;
		this->next = nullptr;
	}
};

