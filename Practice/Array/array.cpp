#include <iostream>
using namespace std;

// TODO: Implement these functions
void reverseArray(int arr[], int size);
int findMax(int arr[], int size);
void rotateArray(int arr[], int size, int positions);
bool isSorted(int arr[], int size);

int main() {
    const int SIZE = 10;
    int arr[SIZE] = {1, 4, 2, 7, 5, 9, 3, 6, 8, 10};
    
    // Problem 1: Print the array
    // TODO: Write code to print all elements of the array
    for (int i:arr){
        cout << i << " ";
    }
    cout << endl;
    
    // Problem 2: Reverse the array
    // TODO: Call your reverseArray function and print the result
    for (int i = SIZE - 1; i >= 0; i--){
        // cout << arr[i] << " ";
    }
    // cout << endl;

    // Problem 3: Find maximum element
    // TODO: Call your findMax function and print the result
    int max = 0;
    for (int m: arr){
        if (m > max) max = m;
    }
    // cout << max << endl;

    // Problem 4: Rotate array by 2 positions
    int arr2[SIZE];
    // First, copy all elements to new array with shifted positions
    for (int i = 0; i < SIZE; i++) {
        // Formula explanation:
        // (i - 2 + SIZE) % SIZE  --> for left rotation
        // (i + 2) % SIZE         --> for right rotation
        
        // For right rotation by 2:
        int newPosition = (i + 2) % SIZE;
        arr2[newPosition] = arr[i];
    }
    
    // Print rotated array
    cout << "Rotated array: ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    // Problem 5: Check if array is sorted
    // TODO: Call your isSorted function and print the result
    int count = 0;
    for (int i = 1; i < SIZE; i ++){
        if (arr[i] >= arr[i - 1]){
            count += 1;
        } 
    }
    cout << count << endl;
    for (int i:arr){
        cout << i << " ";
    }
    cout << endl;

    if (count == SIZE - 1){
        cout << "Array is sorted";
    } else cout << "Array is not sorted";

    return 0;
}
    
// Problem 6: Bubble Sort

// Try to implement these functions on your own!
