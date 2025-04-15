| Content   | Merge Sort | Quick Sort
|-----------|------------|-------------
| Time      | O(nlogn)   | O(n²) 
| Space     | O(n)       | O(n)
| In-place  | No         | Yes
| Partition | Parted into 2 halves - n/2 | Parted into any ratio 
| Usage with dataset | Work well on any type of dataset irrespective of size | Work well on large dataset because it has in-place sorting (log n ) space on the call stack which makes memory efficient + access in sequential order which leads to better cache locality, which is very important when dealing with large arrays stored in RAM or virtual memory + optimization works well 
| Additional Storage | O(n) | O(1)
| Efficiency | Better for linkeld list, stable sorting, massive data that cannot fit into RAM | faster on larger dataset and worst for large disk database (quick sort not designed for external sorting as quick sort need randome access which slow on disk. Bonus: You cannot random access in disk because it requires physical seeking (HDD) or block-level read overhead (SSD) — unlike RAM, which gives true O(1) random access via direct addressing)
| Sorting method | Data that is to be stored cannot be accomodated in the memory and need auxiliary storage Data store in main memory | internal sorting method where the data is sorted in main memory
| Stability | Stable as two elements with equal key appear in the same order in sorted output as they appear in the input array | Unstable in this scenario, but it can be made stable with changes in code