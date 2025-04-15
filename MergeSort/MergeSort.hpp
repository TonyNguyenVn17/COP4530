#ifndef MERGESORT_HPP
#define MERGESORT_HPP


#include <list>
using std::list;

//* Merge two sorted array using Recursion

template<typename E, typename C>
void merge(list<E>& S1, list<E>& S2, list<E>& S, const C& less) {
    typedef typename list<E>::iterator Itor;
    //* Start at the beginning of each array
    Itor p1 = S1.begin();
    Itor p2 = S2.begin();

    //* Compare and merge until one array is empty
    //! This part create 2 temporary list which cost O(n) space
    while (p1 != S1.end() && p2 != S2.end()) {
        // get the smaller value
        if (less(*p1, *p2)) {
            // append value at p1 or p2 to S
            S.push_back(*p1++);
        } else {
            S.push_back(*p2++);
        }
    }

    //* The remaining element is guarantee to be sorted as it is a sorted list, merge it to S
    while (p1 != S1.end()) {
        S.push_back(*p1++);
    }

    while (p2 != S2.end()) {
        S.push_back(*p2++);
    }
}

template<typename E, typename C>
void MergeSort(list<E>& S, const C& less) {
    //* Define an iterator as List type
    typedef typename list<E>::iterator Itor;
    int n = S.size();

    //* Base case
    if (n < 2) return;

    list<E> S1, S2;
    Itor p = S.begin();

    //* Split first half into two subarray
    for (int i = 0; i < n / 2; ++i) {
        S1.push_back(*p++);
    }
    //* Split second half into two subarray
    for (int i = n / 2; i < n; ++i) {
        S2.push_back(*p++);
    }

    //* Clear the original array to reuse it to store merge 
    S.clear();

    //* Recursively split the remaining subarray
    MergeSort(S1, less);
    MergeSort(S2, less);

    //* Merge the two subarray
    merge(S1, S2, S, less);
}

#endif


