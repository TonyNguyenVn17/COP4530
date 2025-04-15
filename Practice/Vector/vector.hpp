#include <iostream>
#include <stdexcept>

class IndexOutOfBounds : public std::runtime_error {
public:
    IndexOutOfBounds(const std::string& msg) : std::runtime_error(msg) {}
};

typedef int Elem;
class ArrayVector{
public:
    ArrayVector(); // constructor
    int size() const; // number of elements
    bool empty() const; // is vector empty?
    Elem& operator[](int i); // element at index i
    Elem& at(int i); // element at index i, throws IndexOutOfBounds if out of bounds

    void erase(int i); // remove element at index
    void insert(int i, const Elem& e); // insert element at index
    void reserve(int N); // reserve at least N spots

private:
    int capacity; // current array size
    int n; // number of elements in vector
    Elem* A; // array storing in elements
};