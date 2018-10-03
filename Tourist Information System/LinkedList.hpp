#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.cpp"

// Link-based implementation of ADT List
// Used in City, Shopping, TourismSystem and Util
template <class T>
class LinkedList
{
private:
   Node<T>* head;
   int itemCount;
   Node<T>* getNodeAt(int position) const;

public:
   LinkedList();
   LinkedList(const LinkedList<T>& aList);
   virtual ~LinkedList();

   bool isEmpty() const;
   int getLength() const;
   void insert(int newPosition, const T& newEntry);
   void remove(int position);
   void clear();

   T getEntry(int position) const;
   void setEntry(int position, const T& newEntry);

   void sort();
};

#endif // LINKED_LIST_HPP
