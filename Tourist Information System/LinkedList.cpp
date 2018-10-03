#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "LinkedList.hpp"
#include "Node.cpp"
#include <cassert> // for assert()

template <class T>
LinkedList<T>::LinkedList() : head(nullptr), itemCount(0)
{
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& aList) : itemCount(aList.itemCount)
{
    Node<T>* oldList = aList.head;

    if (oldList == nullptr)
        head = nullptr;
    else
    {
        head = new Node<T>();
        head->setItem(oldList->getItem());

        Node<T>* newList = head;
        oldList = oldList->getNext();
        while (oldList != nullptr)
        {
            Node<T>* newNode = new Node<T>(oldList->getItem());

            newList->setNext(newNode);

            newList = newList->getNext();

            oldList = oldList->getNext();
        }

        newList->setNext(nullptr);
   }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return itemCount == 0;
}

template <class T>
int LinkedList<T>::getLength() const
{
    return itemCount;
}

template <class T>
void LinkedList<T>::insert(int newPosition, const T& newEntry)
{
    assert((newPosition >= 0) && (newPosition <= itemCount));

    Node<T>* newNode = new Node<T>(newEntry);

    if (newPosition == 0)
    {
        newNode->setNext(head);
        head = newNode;
    }
    else
    {
        Node<T>* prevNode = getNodeAt(newPosition - 1);

        newNode->setNext(prevNode->getNext());
        prevNode->setNext(newNode);
    }

    itemCount++;
}

template <class T>
void LinkedList<T>::remove(int position)
{
    assert((position >= 0) && (position < itemCount));

    Node<T>* nodeToRemove = nullptr;
    if (position == 0)
    {
        nodeToRemove = head;
        head = head->getNext();
    }
    else
    {
        Node<T>* prevNode = getNodeAt(position - 1);

        nodeToRemove = prevNode->getNext();

        prevNode->setNext(nodeToRemove->getNext());
    }

    nodeToRemove->setNext(nullptr);
    delete nodeToRemove;
    nodeToRemove = nullptr;

    itemCount--;
}

template <class T>
void LinkedList<T>::clear()
{
    while (!isEmpty())
        remove(0);
}

template <class T>
T LinkedList<T>::getEntry(int position) const
{
    assert((position >= 0) && (position < itemCount));

    Node<T>* nodePtr = getNodeAt(position);
    return nodePtr->getItem();
}

template <class T>
void LinkedList<T>::setEntry(int position, const T& newEntry)
{
    assert((position >= 0) && (position < itemCount));

    Node<T>* nodePtr = getNodeAt(position);
    nodePtr->setItem(newEntry);
}

template <class T>
Node<T>* LinkedList<T>::getNodeAt(int position) const
{
    assert((position >= 0) && (position < itemCount));

    Node<T>* curNode = head;
    for (int skip = 0; skip < position; skip++)
        curNode = curNode->getNext();

    return curNode;
}

// Do insertion sort
template <class T>
void LinkedList<T>::sort()
{
    // List is empty or has only one element; trivially sorted
    if (isEmpty() || head->getNext() == nullptr)
        return;

    Node<T>* unsortedList = head; // Unsorted list points to actual list
    Node<T>* sortedList = nullptr; // Create an empty sorted list
    while(unsortedList != nullptr) // Traverse the unsorted list
    {
        // For every node of unsorted list, we're going to insert the node in sorted way in sorted list
        Node<T>* currNode = unsortedList;
        unsortedList = unsortedList->getNext();

        // Empty sorted list or current node is smaller than head node of sorted list
        if (sortedList == nullptr || *currNode->getItem() < *sortedList->getItem())
        {
            currNode->setNext(sortedList);
            sortedList = currNode;
        }
        else
        {
            // Insert current node into proper position in non-empty sorted list
            Node<T>* sortedNode = sortedList;
            while (sortedNode != nullptr) // Traverse the sorted list
            {
                // Last node in sorted list or current node is smaller than a node of sorted list
                if (sortedNode->getNext() == nullptr || *currNode->getItem() < *sortedNode->getNext()->getItem())
                {
                    currNode->setNext(sortedNode->getNext());
                    sortedNode->setNext(currNode);
                    break;
                }
                sortedNode = sortedNode->getNext();
            }
        }
    }

    head = sortedList; // List is now sorted
}

#endif // LINKED_LIST_CPP
