#ifndef _PRIORITY_QUEUE_T_
#define _PRIORITY_QUEUE_T_

// Restore the heap after inserting a new node at the end of array
template <typename T>
void PriorityQueue<T>::heapifyUp(int idx) {
    // the node will "bubble up" until it meets a parent > than itself, therefore in the right place
    while (idx > 0) {
        int parent = (idx - 1) / 2; // get parent index
        if (myQueue[parent] < myQueue[idx]) {
            // swap the two node
            T temp = myQueue[parent];
            myQueue[parent] = myQueue[idx];
            myQueue[idx] = temp;

            idx = parent; // swap index
        } 
        else { break; }
    }
}

// Restore heap after the root is removed
template <typename T>
void PriorityQueue<T>::heapifyDown(int idx) {
    int n = myQueue.size();
    while (true) {
        // get 2 indexes of child nodes
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int largest = idx;

        // get index of largest node out of two child node
        if (left < n && myQueue[largest] < myQueue[left]) { largest = left; }
        if (right < n && myQueue[largest] < myQueue[right]) { largest = right; }

        if (largest != idx) {
            // swap the 2 nodes
            T temp = myQueue[idx];
            myQueue[idx] = myQueue[largest];
            myQueue[largest] = temp;

            idx = largest; // swap the index
        } 
        else { break; } // if current node is already larger (already in correct place) then break
    }
}

// Push and pop --------------------------
template <typename T>
void PriorityQueue<T>::push(const T& item) {
    myQueue.push_back(item);
    heapifyUp(myQueue.size() - 1);
}

template <typename T>
void PriorityQueue<T>::pop() {
    if (myQueue.empty()) { return; } // if nothing in queue then return() immediately

    myQueue[0] = myQueue.back();
    myQueue.pop_back();
    heapifyDown(0);
}

// Helper functions --------------------------
template <typename T>
T PriorityQueue<T>::top() {
    return myQueue[0];
}

template <typename T>
bool PriorityQueue<T>::empty() {
    return myQueue.empty();
}

template <typename T>
int PriorityQueue<T>::size() {
    return myQueue.size();
}

#endif 
