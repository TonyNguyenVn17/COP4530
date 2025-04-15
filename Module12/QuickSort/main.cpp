#include <iostream>
#include "QuickSort.hpp"


int main(){
    std::vector<int> nums = {8, 3, 5, 1, 9, 15, 12, 10, 17};
    std::cout << "Original sequence: ";
    for (int x : nums) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    QuickSort(nums, std::less<int>());
    std::cout << "\n";
    std::cout << "Sorted Sequence " << std::endl;
    for (int x : nums) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}