// Minh Thien Nguyen
// U1179 6783

#include "IntDList.hpp"     
#include <iostream>         
#include <stdexcept>      


// Destructure: Cleans up all nodes in the list to prevent memory leaks
IntDLList::~IntDLList() {
    while (!isEmpty()) {
        deleteFromHead();
    }
}

// Adds a new node with the given value at the beginning of the doubly linked list
void IntDLList::addToHead(int value){
    IntDLLNode* newNode = new IntDLLNode(value);
    // Create head and tail if no LL existed
    if (isEmpty()) {
        head = tail = newNode;
    } else { // Add new node to LL
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    // Increase size of LL in memory 
    size++;
}

// Inserts a new node with the given value in ascending order
void IntDLList::insertInOrder(int value) {
    // Add to the front if it's a smallest value
    if (isEmpty() || value <= head->info){
        addToHead(value);
        return;
    }
    
    // Add to the end if it's a largest value
    if (value >= tail->info) {
        addToTail(value);
        return;
    }

    // Find the correct position to start
    IntDLLNode* current = head;
    while (current != nullptr && current->info < value) {
        current = current->next;
    }

    // Insert new node before the current node
    IntDLLNode* newNode = new IntDLLNode(value);
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
    size++;
}

// Adds a new node with the given value at the end of the list
void IntDLList::addToTail(int value) {
    IntDLLNode* newNode = new IntDLLNode(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

// Removes and returns the value at the head of list
// Throws an exception if the list is empty
int IntDLList::deleteFromTail() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot delete from empty list");
    }

    int value = tail->info;
    IntDLLNode* temp = tail;

    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    size--;
    return value;
}

// Removes the first occurence of the specified value from the list
void IntDLList::deleteNode(int value) {
    if (isEmpty()) {
        return;
    }

    // Handle special cases for head and tail
    if (head->info == value) {
        deleteFromHead();
        return;
    }

    if (tail->info == value) {
        deleteFromTail();
        return;
    }

    // Search for node to delete
    IntDLLNode* current = head;
    while (current != nullptr && current->info != value) {
        current = current->next;
    }

    // If found, remove the node and update links
    if (current != nullptr) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }
}

// Checks if a value exists in the list
bool IntDLList::isInList(int value) const {
    IntDLLNode* current = head;
    while (current != nullptr) {
        if (current->info == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Prints all values in the list to standard output
void IntDLList::printAll() const {
    IntDLLNode* current = head;
    while (current != nullptr) {
        std::cout << current->info << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Converts the lsit to a string representation
// Returns a string containing all values concatenated together
std::string IntDLList::addToString() const {
    std::string result;
    IntDLLNode* current = head;

    while (current != nullptr) {
        // Convert int to char by adding '0' and append to string
        result += std::to_string(current->info);
        current = current->next;
    }

    return result;
}

// Add this implementation for deleteFromHead()
int IntDLList::deleteFromHead() {
    if (head == nullptr) {
        throw std::runtime_error("Cannot delete from empty list");
    }

    int value = head->info;
    IntDLLNode* temp = head;
    head = head->next;
    
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        // List becomes empty
        tail = nullptr;
    }

    delete temp;
    size--;
    return value;
}


