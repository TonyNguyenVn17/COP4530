// Minh Thien Nguyen
// U1179 6783

#ifndef INTDLIST_NODE_HPP
#define INTDLIST_NODE_HPP

#include <string>
#include "IntDList_node.hpp"

class IntDLList {
private:
    IntDLLNode *head, *tail;
    int size;

public:
    IntDLList() : head(nullptr), tail(nullptr), size(0) {}
    ~IntDLList();

    // Require methods
    void addToHead(int);
    void insertInOrder(int);
    void addToTail(int);
    int deleteFromHead();
    int deleteFromTail();
    void deleteNode(int);
    bool isInList(int) const;
    void printAll() const;
    std::string addToString() const;
    bool isEmpty() const { return head == nullptr;}

};
#endif 