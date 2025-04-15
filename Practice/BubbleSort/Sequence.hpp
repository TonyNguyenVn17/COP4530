#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <vector>
#include <stdexcept>

class Sequence {
public:
    class Iterator {
    public:
        Iterator(int* ptr) : ptr(ptr) {}
        int& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    private:
        int* ptr;
    };

    Sequence() {}

    void add(int value) {
        data.push_back(value);
    }

    int size() const {
        return data.size();
    }

    Iterator atIndex(int index) {
        if (index < 0 || index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return Iterator(&data[index]);
    }

    Iterator begin() {
        return Iterator(&data[0]);
    }

    Iterator end() {
        return Iterator(&data[0] + size());
    }

    void clear() {
        data.clear();
    }

private:
    std::vector<int> data;
};

#endif // SEQUENCE_HPP