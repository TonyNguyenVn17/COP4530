#ifndef MERGESORT_VECTOR
#define MERGESORT_VECTOR

#include <vector>
#include <utility> // for std::swap
using std::vector;

/*
 - Merge two sorted subarrays from 'in' into 'out' starting at position 'b'
 - First subarray: in[b ... b + m - 1]
 - Second subarray: in[b + m ... b + 2m - 1] (or until the end of the array)
 - Elements are merged in order defined by 'less' (i.e., smallest comes first)
*/
//todo - Time Complexity = O(n) as we loop through each array only once worst case
template<typename E, typename C>
void merge(vector<E>& in, vector<E>& out, const C& less, int b, int m) {
    //* both index depends on b and m as we are merging array starting from b and end at b + m (size)
    int i = b;          // index into run #1
    int j = b + m;      // index into run #2
    int n = in.size();

    //* we do min to make sure both doesn't go pass the array size 
    int leftArray = std::min(b + m, n);    // to end of leftsubarray
    int rightArray = std::min(b + 2*m, n);  // end of second subarray
    int k = b; // write position in out-array

    // compare element by elemment from both vector, stop when one out of bound
    while ((i < leftArray) && (j < rightArray)) {
        // append smaller to S
        if(!less(in[j], in[i]))
            out[k++] = in[i++];      
        else 
            out[k++] = in[j++];
    }

    // append the remaining to the merged array
    while (i < leftArray)
        out[k++] = in[i++];        
    while (j < rightArray)  
        out[k++] = in[j++];       
}

//todo - Time complexity = O(logn) as each merge sort call divide the array in half + O(n) for each merge operation = O(nlogn)
template <typename E, typename C>
void MergeSortVector(vector<E>& S, const C& less){
    // create an alias 'vect' to represent a vector of any type
    typedef vector<E> vect;
    int n = S.size();

    // initialize initial input and output vector
    // this takes O(n) space overall
    vect v1(S); vect* in = &v1;     
    vect v2(S); vect* out = &v2;    

    // m is the amount of element in each subarray
    // b is the starting index of the subarray
    for (int m = 1; m < n; m *= 2) {
        // b += 2m because the merge size increase based on m
        for (int b = 0; b < n; b += 2 * m) {
            merge(*in, *out, less, b, m);
        }
        std::swap(in, out);
    }
    S = *in;
}


#endif