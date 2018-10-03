#ifndef LINKED_STACK_CPP
#define LINKED_STACK_CPP

#include "LinkedStack.hpp"
#include "Node.cpp"
#include <cassert> // for assert()

template <class T>
LinkedStack<T>::LinkedStack() : top(nullptr)
{
}

template <class T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& aStack)
{
   Node<T>* oldStack = aStack.top;

   if (oldStack == nullptr)
      top = nullptr;
   else
   {
      top = new Node<T>(oldStack->getItem());

      Node<T>* newStack = top;

      oldStack = oldStack->getNext();

      while (oldStack != nullptr)
      {
         Node<T>* newNode = new Node<T>(oldStack->getItem());

         newStack->setNext(newNode);

         newStack = newStack->getNext();

         oldStack = oldStack->getNext();
      }

      newStack->setNext(nullptr);
   }
}

template <class T>
LinkedStack<T>::~LinkedStack()
{
	while (!isEmpty())
		pop();
}

template <class T>
bool LinkedStack<T>::isEmpty() const
{
	return top == nullptr;
}

template <class T>
void LinkedStack<T>::push(const T& newItem)
{
	Node<T>* newNode = new Node<T>(newItem, top);
	top = newNode;
    newNode = nullptr;
}

template <class T>
void LinkedStack<T>::pop()
{
	assert(!isEmpty());

    Node<T>* nodeToDelete = top;
    top = top->getNext();

    nodeToDelete->setNext(nullptr);
    delete nodeToDelete;
    nodeToDelete = nullptr;
}

template <class T>
T LinkedStack<T>::peek() const
{
	assert(!isEmpty());

	return top->getItem();
}

#endif // LINKED_STACK_CPP
