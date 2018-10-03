#ifndef NODE_CPP
#define NODE_CPP

#include "Node.hpp"

template <class T>
Node<T>::Node() : next(nullptr)
{
}

template <class T>
Node<T>::Node(const T& item) : item(item), next(nullptr)
{
}

template <class T>
Node<T>::Node(const T& item, Node<T>* next) : item(item), next(next)
{
}

template <class T>
void Node<T>::setItem(const T& newItem)
{
    item = newItem;
}

template <class T>
void Node<T>::setNext(Node<T>* newNext)
{
    next = newNext;
}

template <class T>
T Node<T>::getItem() const
{
    return item;
}

template <class T>
Node<T>* Node<T>::getNext() const
{
    return next;
}

#endif // NODE_CPP
