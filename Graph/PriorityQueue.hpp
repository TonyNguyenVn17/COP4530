#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <vector>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> myQueue;

    void heapifyUp(int idx);
    void heapifyDown(int idx);

public:
    void push(const T& item);
    void pop();
    T top();
    bool empty();
    int size();
};

#include "PriorityQueue.tpp" 

#endif 