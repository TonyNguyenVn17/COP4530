# Merge Sort

## Definition
- Merge sort is a sorting algorithm that works by dividing an array into smaller subarrays, sorting each subarray, and then merging the sorted subarrays back together to form the final sorted array.

## Time Complexity
- The height **h** of the merge-sort tree is **O(logn)** at each recursive call we divide half the sequence
- The overall amount or work done at the nodes of depth **i** is **O(n)** (It's O(n) work per level primarily because of the combine step (like the merge step in Merge Sort) that happens after the splits.)
    - We partition and merge **2^i** sequence (as each level the amount of nodes is double the previous level) of size **n/2^i**
    - We make **2^(i+1)** calls to merge
    - Each call to merge takes **O(n/2^i)**
    - The total work done at depth **i** is **O(2^(i+1) * n/2^i) = O(n)**
- The total work done is **O(nlogn)** (Worst and Average)
- In simple term:
    - It takes **O(n)** to merge the two halves
    - It takes **O(logn)** to split the array into two halves recursively
    - Therefore, the total time complexity is **O(nlogn)**


## Space Complexity
- Merge Sort works by dividing the array and then merging two sorted halves into a new array.
- The merge step requires temporary arrays to hold elements from the left and right halves.
### Recursive Implementation - List
- We split S by physically creating two new lists S1 and S2
- Then you recursively sort each half
- Then finally merge S1 and S2 back into S
- So at any point in recursion, we store:
    - Original list S (emptied during merge)
    - Two lists S1 and S2 (contain copied data)
- So we create new lists, which hold copies of the original elements (or at least references).
Over the full recursion, the total space is O(n).
- The call stack adds O(log n), but that's minor.
- So overall, the space complexity is **O(n)**.

### Iterative Implementation - Vector
- We don’t use recursion at all
- We create two full-size vectors: v1, v2
- Weread from one, write into the other, and then swap
- No extra vector copies are created during merging
- We use 2 full buffers -- v1 and v2, each of size n
- That's 2n space exactly — constant over time, doesn’t grow
- So overall space: O(n), but more controlled and iterative