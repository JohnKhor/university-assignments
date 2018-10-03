#ifndef NODE_HPP
#define NODE_HPP

// Used in LinkedList and LinkedStack
template <class T>
class Node
{
private:
    T item;
    Node<T>* next;

public:
    Node();
    Node(const T& item);
    Node(const T& item, Node<T>* next);

    void setItem(const T& newItem);
    void setNext(Node<T>* newNext);

    T getItem() const ;
    Node<T>* getNext() const ;
};

#endif // NODE_HPP
