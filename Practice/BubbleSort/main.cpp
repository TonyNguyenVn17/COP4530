#include <iostream>
#include <chrono>
#include "Sequence.hpp"
#include "BubbleSort.hpp"

void analyzeSortTime(void (*sortFunc)(Sequence&), Sequence& S, const std::string& sortName) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(S);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << sortName << " took " << duration.count() << " seconds." << std::endl;
}

int main() {
    Sequence S;
    S.add(5);
    S.add(3);
    S.add(8);
    S.add(1);
    S.add(2);

    std::cout << "Original sequence: ";
    for (Sequence::Iterator it = S.begin(); it != S.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    analyzeSortTime(bubbleSort1, S, "BubbleSort1");

    std::cout << "Sorted sequence: ";
    for (Sequence::Iterator it = S.begin(); it != S.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    S.clear();
    S.add(10);
    S.add(100);
    S.add(98);
    S.add(12);
    S.add(1);
    std::cout << "Original sequence 2: ";
    for (Sequence::Iterator it = S.begin(); it != S.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    analyzeSortTime(bubbleSort2, S, "BubbleSort2");

    std::cout << "Sorted sequence 2: ";
    for (Sequence::Iterator it = S.begin(); it != S.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}