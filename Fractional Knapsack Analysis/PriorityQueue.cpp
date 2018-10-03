#include <iostream>
#include <stdexcept> // runtime_error
#include <iomanip> // setw, fixed, setprecision

#include "PriorityQueue.hpp"

bool operator>(const Item& item1, const Item& item2) {
    return item1.value > item2.value;
}

void PriorityQueue::swap(int i, int j) {
    Item temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

int PriorityQueue::getParentIndex(int i) { return i / 2; }
int PriorityQueue::getLeftIndex(int i) { return 2 * i; }
int PriorityQueue::getRightIndex(int i) { return 2 * i + 1; }

void PriorityQueue::heapifyUp(int i) {
    // Swap if current item has a higher value than its parent
    while(i != 0 && heap[i] > heap[getParentIndex(i)]) {
        swap(i, getParentIndex(i));
        i = getParentIndex(i);
    }
}

void PriorityQueue::heapifyDown(int i) {
    int leftIndex = getLeftIndex(i);
    int rightIndex = getRightIndex(i);
    int maxIndex = i;

    if (leftIndex < size && heap[leftIndex] > heap[i])
        maxIndex = leftIndex;
    if (rightIndex < size && heap[rightIndex] > heap[maxIndex])
        maxIndex = rightIndex;

    // Swap if either left or right child has a higher value than current item
    if (maxIndex != i) {
        swap(i, maxIndex);
        heapifyDown(maxIndex);
    }
}

PriorityQueue::PriorityQueue(int capacity) : capacity(capacity), size(0) {
    heap = new Item[capacity];
}

bool PriorityQueue::isEmpty() { return size == 0; }

void PriorityQueue::enqueue(Item item) {
    if (size == capacity)
        throw std::runtime_error("Unable to enqueue due to heap is full.");

    size++;
    heap[size - 1] = item; // Append item as last child
    heapifyUp(size - 1); // Swap upwards if the item has a larger value than its parent
}

Item PriorityQueue::dequeue() {
    if (size == 0)
        throw std::runtime_error("Unable to dequeue due to heap is empty.");

    Item root = heap[0];
    heap[0] = heap[size - 1]; // Put last child as new root
    size--;
    heapifyDown(0); // Swap downwards if the new root has a smaller value than its child

    return root;
}

void PriorityQueue::print() {
    std::cout << "No    | Benefit | Weight | Value" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(5) << heap[i].no << " | ";
        std::cout << std::setw(7) << heap[i].benefit << " | ";
        std::cout << std::setw(6) << heap[i].weight << " | ";
        std::cout << std::setw(5) << std::fixed << std::setprecision(2) << heap[i].value << std::endl;
    }
    std::cout << std::endl;
}

PriorityQueue::~PriorityQueue() {
    delete [] heap;
}
