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

## Code
### Merge Sort
```
    void merge(list<E>& S1, lsit<E>& S2, list<E>& S, const C& less)  {
        typedef typename list<E>::iterator Itor;

        Itor p1 = S1.begin();
        Itor p2 = S2.begin();

        while (p1 != S1.end() && p2 != S2.end()) {
            if (less(*p1, *p2)) {
                S.push_back(*p1++)
            } else {
                S.push_back(*p2++);
            }
        }

        // merge the remaining eleemnt
        while (p1 != S1.end()) {
            S.push_back(*p1++);
        };
        
        while (p2 != S2.end()) {
            S.push_back(*p2++);
        }
    }

tempalte<typename E, typename C>
void MergeSort(list<E>& S, const C& less) {
    typedef typpename list<E>:: iterator Itor;
    int n = S.size();

    if (n < 2) return;

    // Split first half
    for (int i = 0; i < n/2; i++) {
        S1.push_back(*p++);
    }

    // Split second half
    for (int i = n/2; i < n; i++){
        S2.push_back(*p++);
    }

    // Clear original array to reuse
    S.clear();

    MergeSort(S1, less);
    MergeSort(S2, less);

    merge(S1, S2, S, less);
}
```

### Quick Sort
```
void QuickSort(std::vector<E>& S, int a, int b, const C& less) {
    if (a>=b) return;

    E picot = S[b];
    
    int l = a;
    int r = b - 1;

    while (l<=r){
        // find the first value greater than pivot
        while (l <= r && less(S[l], pivot)) {
            l ++;
        }

        // find the first value less than pivot
        while (l <= r && less(pivot, S[r])) {
            r --;
        }

        // if left and right not crossed, swap as they are in wrong position
        if (l <= r) {
            std::swap(S[l], S[r]);
        }
    }

    std::swap(S[l], S[b]);

    QuickSort(S, a, l - 1, less);
    QuickSort(S, l + 1, r, less);
}
```
