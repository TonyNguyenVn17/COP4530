#include <iostream>
#include "vector.hpp"

// constructor
ArrayVector::ArrayVector() : capacity(0), n(0), A(NULL) { }

// is vector empty
bool ArrayVector::empty() const { return size() == 0; }

// number of elements
int ArrayVector::size() const { return n;}

// element at index
Elem& ArrayVector::operator[] (int i) { return A[i]; }

// element at index with bounds checking
Elem& ArrayVector::at(int i) {
    if (i < 0 || i >= n) {
        throw std::out_of_range("Index out of bounds");
    }
    return A[i];
}