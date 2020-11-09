#include <iostream>
#include "stack.h";

using namespace std;


int main()
{
	Stack<int> myStack;

	myStack.push(12);
	myStack.push(13);
	myStack.push(27);
	myStack.push(19);
	myStack.push(313);
	myStack.printStack();
	//myStack.pop();
	//myStack.pop();
	cout << endl;
	myStack.insert(3, 79);
	myStack.printStack();
}


// add new node to the top of the stack
template<typename T>
void Stack<T>::push(T data)
{
	// add first
	if (size == 0)
	{
		top = new Node<T>(data);
		bottom = top;
		size++;
	}
	else
	{
		// add new node to top
		Node<T>* tmp = new Node<T>(data);
		tmp->next = top;
		top = tmp;
		size++;
	}
}

// remove a node from atop the stack
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
		Node<T>* tmp;
		tmp = top->next;
		delete top;
		top = tmp;
		size--;
	}
}

template<typename T>
void Stack<T>::printStack()
{
	Node<T>* tmp = top;

	cout << "Top " << endl;
	while (tmp != nullptr)
	{
		cout << "__" << endl;
		cout << tmp->data << endl;
		tmp = tmp->next;
	}
	cout << endl;
	cout << "Bottom" << endl;
}


template<typename T>
void Stack<T>::insert(int index, T data)
{
	// ensure valid index
	if (index < 0 || index > size - 1)
	{
		cout << "Invalid index" << endl;
		return;
	}
	else if (index == 0)
	{
		push(data);
	}
	else
	{
		Node<T>* tmp = top;
		for (int i = 0; i < index-1; i++)
		{
			tmp = tmp->next;
		}
		// create new node w/ new data input
		Node<T>* new_node = new Node<T>(data);

		// point new node to what previous node references
		new_node->next = tmp->next;

		// point previous node to new_node
		tmp->next = new_node;
	}
}