#include <iostream>
#include "stack.h";

using namespace std;


int main()
{
	// create stack object of integer type
	Stack<int> myStack;
	
	// operations to test our stack making sure everything works.
	myStack.push(12);
	myStack.push(13);
	myStack.push(27);
	myStack.push(19);
	myStack.push(313);
	myStack.printStack();
	myStack.pop();
	myStack.pop();
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
		// new node as top
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
	// make sure to see if stack is not empty
	if (size == 0)
	{
		cout << "Cannot pop off an empty stack" << endl;
		return;
	}
	else
	{
		// create tmp node and assign it to node after top
		// remove top and reassign top.
		Node<T>* tmp;
		tmp = top->next;
		delete top;
		top = tmp;
		size--;
	}
}

// print out the contents of stack from Top -> Bottom
template<typename T>
void Stack<T>::printStack()
{
	// tmp node
	Node<T>* tmp = top;

	cout << "Top " << endl;
	
	// traverse so as long as temp pointer isnt pointing to nothing.
	while (tmp != nullptr)
	{
		cout << "__" << endl;
		cout << tmp->data << endl;
		tmp = tmp->next;
	}
	cout << endl;
	cout << "Bottom" << endl;
}

// insert a data into the stack at specified index.
// Index 0 being the top and bottom being size-1
template<typename T>
void Stack<T>::insert(int index, T data)
{
	// ensure valid index
	if (index < 0 || index > size - 1)
	{
		cout << "Invalid index" << endl;
		return;
	}
	// if the index is top then call push()
	else if (index == 0)
	{
		push(data);
	}
	else
	{
		// otherwise traverse to node right before index of interest
		// make new node point to node at index of interst
		// make previous node reference new node
		// this is done in this specific order so as to not orphan the stack and to avoid memory leaks
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
