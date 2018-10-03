#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "Item.hpp"

class PriorityQueue {
private:
    int capacity;
    int size;
    Item* heap;

    friend bool operator>(const Item &item1, const Item &item2);
    void swap(int i, int j);

    int getParentIndex(int i);
    int getLeftIndex(int i);
    int getRightIndex(int i);

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    PriorityQueue(int capacity);

    bool isEmpty();

    void enqueue(Item item);
    Item dequeue();

    void print();

    ~PriorityQueue();
};

#endif // PRIORITY_QUEUE_HPP
