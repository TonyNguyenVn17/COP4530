#include <list>
#include <vector>
#include <utility>
#include <iostream>

#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP


//* Quick Sort implementation for Vector

/*
    if S.size() <= 1 then
        return {S is already sorted}
    p <- S.back().element // choose the pivot

    Inititialize empty sequence: L, E, G

    * Partition step: scan S backwards
    while S is not empty:
        x <- last element of S
        if x < p:
            move x from S to the back of L
        else if x = p:  
            move x from S to the back of E
        else:
            move x from S to the back of G

    * Recursive calls on L and G
    QuickSort(L)
    QuickSort(G)

    * Rebuild S by appending sorted elements
    while L is not empty:
        move from eleemnt of L to the back of S
    while E is not empty:
        move from eleemnt of E to the back of S
    while G is not empty:
        move from eleemnt of G to the back of S
    
    return

    ! Sample tracing
    QuickSort([9, 3, 7, 1])
    → pivot = 1 → L=[], E=[1], G=[9, 3, 7]
        → QuickSort([9, 3, 7])
        → pivot = 9 → L=[3, 7], E=[9], G=[]
            → QuickSort([3, 7])
            → pivot = 7 → L=[3], E=[7], G=[]
                → QuickSort([3]) 
                → QuickSort([]) 
            ← [3, 7]
        ← [3, 7, 9]
    ← [1, 3, 7, 9]

*/

/**
 * @param array 
 * @param a = left index
 * @param b = right index
 * @param less  = comparator
 */
template <typename E, typename C>
void QuickSortStep(std::vector<E>& S, int a, int b, const C& less) {
    // base case
    if (a >= b) return;

    E pivot = S[b]; // pick last element as pivot
    std::cout << "Pivot = " << pivot << ", Subarray = [";
    for (int i = a; i <=b; i++)  std::cout << S[i] << (i < b ? ", " : "");
    std::cout << "]" << std::endl << std::endl;


    int l = a; // left edge
    int r = b - 1; // right edge (exclude pivot)

    // loop until index cross
    while (l <= r) {
        // scan to find value that larger than pivot
        while (l <= r && less(S[l], pivot)) {
            l ++;
        }
        // scan to find value that smaller than pivot
        while (r >= l && less(pivot, S[r])) {
            r --;
        }

        // if index haven't cross, swap them 
        if (l < r) { 
            std::cout << " Swapped " << S[l] << " and " << S[r] << std::endl << std::endl;
            std::swap(S[l], S[r]); 
        } 
    }
    // move left value to last position as left is the first position where value is >= pivot
    std::swap(S[l], S[b]);
    std::cout << "Placed pivot " << pivot << " at " << l << std::endl << std::endl;

    // Recursively sort the left partition: all elements before the pivot
    QuickSortStep(S, a, l - 1, less); 
    // Recursively sort the right partition: all elements after the pivot
    QuickSortStep(S, l + 1, b, less); 

}

template <typename E, typename C>
void QuickSort(std::vector<E>& S, const C& less) {
    if (S.size() <= 1) return;
    QuickSortStep(S, 0, S.size() - 1, less); // call sort utility
}

#endif