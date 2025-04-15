#include <iostream>
#include <list>
#include <functional>  // for std::less
#include "MergeSort.hpp"
#include "MergeSortVector.hpp"

int main() {
    std::list<int> nums = {8, 3, 5, 1, 9};
    
    // List-Implementation Sort
    MergeSort(nums, std::less<int>());

    for (int x : nums) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::vector<int> nums_v = {8, 3, 5, 1, 9};
    // Vector-Implementation Sort
    MergeSortVector(nums_v, std::less<int>());
    for (int x : nums_v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;


    return 0;
}
