//Header File: linkedStack.h 

// header file declarations/ macro definitions
// # pragma once is also acceptable for some windows machines
#ifndef H_StackType
#define H_StackType
 
// input/output stream library 
#include <iostream>
// gives us assert
#include <cassert> 
 // stack header file
#include "stackADT.h"

// namespace for std:: lib
using namespace std;

//generic, so as to implement any data type
template <class Type>
// struct used instead of class, not a big difference here, comparatively 
struct nodeType
{
    //data element
    Type info;
    // pointer to another node of same data type
    nodeType<Type> *link;
};

// generic class
template <class Type>
//Stack class with generic data type
class linkedStackType: public stackADT<Type>
{
public:
     // overloading the assignment operation so as to assign data
     // the left hand side is a stacktype and so is the right hand side
    const linkedStackType<Type>& operator= (const linkedStackType<Type>&);
    
    bool isEmptyStack() const;
      //Function to determine whether the stack is empty.
      //Postcondition: Returns true if the stack is empty;
      //               otherwise returns false.

    bool isFullStack() const;
      //Function to determine whether the stack is full.
      //Postcondition: Returns false.

    void initializeStack();
      //Function to initialize the stack to an empty state. 
      //Postcondition: The stack elements are removed; 
      //               stackTop = nullptr;

    void push(const Type& newItem);
      //Function to add newItem to the stack.
      //Precondition: The stack exists and is not full.
      //Postcondition: The stack is changed and newItem 
      //               is added to the top of the stack.

    Type top() const;
      //Function to return the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: If the stack is empty, the program 
      //               terminates; otherwise, the top 
      //               element of the stack is returned.

    void pop();
      //Function to remove the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: The stack is changed and the top 
      //               element is removed from the stack.

    linkedStackType(); 
      //Default constructor
      //Postcondition: stackTop = nullptr;

    linkedStackType(const linkedStackType<Type>& otherStack); 
      //Copy constructor

    ~linkedStackType();
      //Destructor
      //Postcondition: All the elements of the stack are 
      //               removed from the stack.

private:
    nodeType<Type> *stackTop; //pointer to the stack

    void copyStack(const linkedStackType<Type>& otherStack); 
      //Function to make a copy of otherStack.
      //Postcondition: A copy of otherStack is created and
      //               assigned to this stack.
};


    //Default constructor
// generic, so as to include any data type
template <class Type> 
// constructor defined via scope resolution operation outside the class declaration
linkedStackType<Type>::linkedStackType()
{  
    // because the stack empty, there is no top element to start with
    stackTop = nullptr;
}

// generic, so as to include any data type
template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{ 
    // returns true if the top most element, being a pointer address nothing
    // hence the stack is empty
    return(stackTop == nullptr);
} //end isEmptyStack

template <class Type>
bool linkedStackType<Type>:: isFullStack() const
{
   // this has been hardcoded to always return false
   // this is most likely because a linked-list based Stack can never be "Full" because all the memory is allocated non-contigously 
    return false;
} //end isFullStack

template <class Type>
void linkedStackType<Type>:: initializeStack()
{
   // custom pointer to type node of generic type
    nodeType<Type> *temp; //pointer to delete the node
   
   // as long as the stack is not empty
    while (stackTop != nullptr)  //while there are elements in 
                              //the stack
    {
      // we want delete the node that temp references and traverse the top node by one
        temp = stackTop;    //set temp to point to the 
                            //current node
        stackTop = stackTop->link;  //advance stackTop to the
                                    //next node
        delete temp;    //deallocate memory occupied by temp
    }
} //end initializeStack

// generic, so as to include any data type
template <class Type>
// function defined via scope resolution operator
// takes in a newElement by reference 
void linkedStackType<Type>::push(const Type& newElement)
{
    // A pointer to a nodeType of generic type
    nodeType<Type> *newNode;  //pointer to create the new node
    
    // Dynamically allocate memory for the new node and reference it using the pointer just created
    newNode = new nodeType<Type>; //create the node

    /* here were are using the "->" operator
       Essentially because we want to reference the object pointed to by newNode and get access to one its data members
       In this case 'info', "->" is equivalent to dereferencing + dot notation *(newNode).info
       The newly created Node now added to the top must reference the current top node and top pointer is reassigned.
    */
    newNode->info = newElement; //store newElement in the node
    newNode->link = stackTop; //insert newNode before stackTop
    stackTop = newNode;       //set stackTop to point to the 
                              //top node
} //end push


// generic, so as to include every data type
template <class Type>
// scope resolution operation to define function outside of class declaration.
Type linkedStackType<Type>::top() const
{
    // checks to make sure the top points to the next corresponding node and not NULL and top the code.
    assert(stackTop != nullptr); //if stack is empty,
                              //terminate the program
    // reference the object pointed to and access into data member
    return stackTop->info;    //return the top element 
}//end top

// generic, so as to include any data type
template <class Type>
// aim is to remove the top most node, because a stack is LIFO based
// So only the top most node can be removed
void linkedStackType<Type>::pop()
{
    // pointer that references a node of generic type
    nodeType<Type> *temp;   //pointer to deallocate memory
    
    // ensure the top pointer isnt pointing empty, so as not to delete nothing
    if (stackTop != nullptr)
    {
        // temporary node pointer referencing the top most
        temp = stackTop;  //set temp to point to the top node
        
        // reassign the top most pointer to the next node using "->" operation
        stackTop = stackTop->link;  //advance stackTop to the 
                                    //next node
     
        // free memory so as to not have leaks.
        delete temp;    //delete the top node
    }
    else
        // if the stack is empty, print to console.
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type> 
// generic method to copy an entire stack into another stack by reference
void linkedStackType<Type>::copyStack
                     (const linkedStackType<Type>& otherStack)
{
    // pointers to nodetype generics, a new one, current and previous.
    nodeType<Type> *newNode, *current, *last;
    
    // ensure the stack is empty
    if (stackTop != nullptr) //if stack is nonempty, make it empty
        initializeStack();
    
    // if the second stack top points to nothing, making current stack also point to nothing
    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    else
    {
        // the current node is referencing the top most
        current = otherStack.stackTop;  //set current to point
                                   //to the stack to be copied

        //copy the stackTop element of the stack 
        stackTop = new nodeType<Type>;  //create the node
        
        // copy the stack top node from one stack to the other
        stackTop->info = current->info; //copy the info
        stackTop->link = nullptr;  //set the link field of the
                                //node to nullptr
        last = stackTop;        //set last to point to the node
        current = current->link;    //set current to point to
                                    //the next node

        //copy the remaining stack until the current node pointer references nothing and then break
        while (current != nullptr)
        {
            // pointer new a new node dynamically allocated
            newNode = new nodeType<Type>;
           
            // copy the info from one node to another
            newNode->info = current->info;
            // newNode points to nothing
            newNode->link = nullptr;
            // The last node's next references the newNode
            last->link = newNode;
            // Make the last node reference the newNode
            last = newNode;
            // traverse to next node
            current = current->link;
        }//end while
    }//end else
} //end copyStack

//copy constructor
// generic, so as to include any data type
template <class Type>
// scope resolution operator in order to define function outside of class declaration.
linkedStackType<Type>::linkedStackType(
                      const linkedStackType<Type>& otherStack)
{
    // top points to nothing 
    stackTop = nullptr;
    // call this.copyStack method with other stack.
    copyStack(otherStack);
}//end copy constructor

    //destructor
template <class Type> 
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}//end destructor

    //overloading the assignment operator
template <class Type>   
const linkedStackType<Type>& linkedStackType<Type>::operator=
    			  (const linkedStackType<Type>& otherStack)
{ 
 // overloading operator so as to 
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);

    return *this; 
}//end operator=

#endif
