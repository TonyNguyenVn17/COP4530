#include <vector>
#include <utility>
#include <iostream>


#ifndef QUICKSORT_B_HPP
#define QUICKSORT_B_HPP

template <typename E, typename C>
/**
 * @param array
 * @param a = left index
 * @param b = right index
 * @param less = comparator
*/
void QuickSortB(std::vector<E>& S, int a, int b, const C& less) {
    // base case
    if (a >= b) return;

    // set the last element as pivot
    E pivot = S[b];

    // print the subarray
    std::cout<<"Pivot = " << pivot << ", Subarray = ";
    for (int i = 0; i <= b; i++) std::cout << S[i];  
    std::cout << "]" << std::endl << std::endl;

    // initialize left edge and right edge
    int l = a;
    int r = b - 1; // -1 as we exclude ouput

    // while left and right index not cross, loop to find larger and smaller value to pivot
    while (l <= r){
        // loop until larger value is found from the left
        while (l <= r && !less(S[l], pivot)) {
            l ++;
        }
        // loop until smaller value is found from the right
        while (l <= r && less(S[r], pivot)) {
            r--;
        }
        // if index haven't cross 
    }
}


#endif