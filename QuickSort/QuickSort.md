# Quick Sort
- **Divide**: If S has at least two elements, select a specific eleemt x from S, which is called the **pivot**. As is common practice, choose the pivot x to be the last element in S. Remove all the elements from S and put them into three sequences:
    - L, storing the elements in S less than x
    - E, storing the elements in S equal to x
    - G, storing the elements in S greater than x
- **Recur**: Recursively sort sequences L and G
- **Conquer**: Put back the elements into S in order by first inserting the elements of L, then the elements of E, and finally the elements of G.

## Algorithm
- We perform the scanning backwards, since removing elements from the end as it's more efficient with constant-time operation: ```pop_back()```
- We perform this latter set of copies in the forward direction, since inserting elements at the end of a sequence is a constant-time operation: ```push_back()```

### Parameter
Input: Sequence S implemented as an array or linked list
Output: The sequence S in sorted order



## Time Complexity 
- The height of quick-sort associated with an execution of quick-sort is linear in worst case
    - This happen if the sequence consists of n distinct elements and is already sorted
- The analyze QuickSort using a tree model called the QuickSort tree
- Everytime QuickSort splits an array, it creates new nodes in this tree
- Each node in the tree represents one recursive call
- The amount of work at each node = size of the input for that call
- Worst case: **O(n²)** as you do linear work `n` times, and the tree is deep: `n - 1`
- Best case: **O(nlogn)** as you do linear work `n` times, and the tree is shallow: `logn`

### Key Idea
- If QuickSort always picks the worst pivot (largest or smallest), then it does not split the array in half, instead just removes one element (the pivot) and recurses on the rest
    - Each level reduces the input by 1
    - The tree become deep: heigh = n - 1

### Math
```
Total work = s₀ + s₁ + s₂ + ... + sₙ₋₁
           ≤ n + (n - 1) + (n - 2) + ... + 1
           = O(n²)
```

## Space Complexity 
- The recursion of QuickSort is highly dependent on the choice of the pivot
    - Best Case: when the pivot divides the array into two equal halves, the space complexity is O(logn)
    - Worst Case: when the pivot is the smallest or largest element, the space complexity is O(n)
- In-place soring:
    - Rearranges element within the original array (in-place swap after comparing pivot with l and right)
    - No extra space is required
