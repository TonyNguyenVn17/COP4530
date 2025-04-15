#ifndef BUBBLE_SORT
#define BUBBLE_SORT


#include "Sequence.hpp"

void bubbleSort1(Sequence& S)
{
    int n = S.size();
    for (int i = 0; i < n; i++){
        for (int j = 1; j < n; j++){
            Sequence::Iterator pred = S.atIndex(j-1); // predecessor
            Sequence::Iterator succ = S.atIndex(j); // successor
            if (*pred > *succ) { // swap if out of order
                int tmp = *pred;
                *pred = *succ;
                *succ = tmp;
            }
        }
    }
}

void bubbleSort2(Sequence& S)
{
    int n = S.size();
    for (int i = 0; i < n; i++){
        Sequence::Iterator pred = S.begin();
        for (int j = 1; j < n-i; j++){
            Sequence::Iterator succ = pred;
            ++succ; // succesor
            if (*pred > *succ) {
                int tmp = *pred;
                *pred = *succ;
                *succ = tmp;
            }
        ++pred;
        }
    }
}

#endif