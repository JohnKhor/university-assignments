#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

#include "Node.cpp"

// Link-based implementation of ADT Stack
// Used in AdjacencyMatrix
template <class T>
class LinkedStack
{
private:
	Node<T>* top;

public:
	LinkedStack();
    LinkedStack(const LinkedStack<T>& aStack);
	virtual ~LinkedStack();

	bool isEmpty() const;
	void push(const T& newItem);
	void pop();
	T peek() const;
};


#endif // LINKED_STACK_HPP
