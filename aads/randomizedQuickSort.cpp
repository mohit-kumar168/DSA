#include <iostream>
#include <vector>
using namespace std;

// Function to partition the array around a pivot
int partition(vector<int> &arr, int low, int high) {
  int pivot = arr[high]; // pivot is the last element
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }

  swap(arr[i + 1], arr[high]);
  return (i + 1);
}

// Function to pick a random pivot and partition
int randomizedPartition(vector<int> &arr, int low, int high) {
  int randomIndex = low + rand() % (high - low + 1); // pick random index
  swap(arr[randomIndex], arr[high]);                 // put random pivot at end
  return partition(arr, low, high);
}

// Recursive Randomized Quick Sort
void randomizedQuickSort(vector<int> &arr, int low, int high) {
  if (low < high) {
    int pi = randomizedPartition(arr, low, high);

    randomizedQuickSort(arr, low, pi - 1);  // sort left part
    randomizedQuickSort(arr, pi + 1, high); // sort right part
  }
}

int main() {
  srand(time(0)); // Seed for random number generator

  vector<int> arr = {10, 7, 8, 9, 1, 5};
  int n = arr.size();

  cout << "Original array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  randomizedQuickSort(arr, 0, n - 1);

  cout << "Sorted array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  return 0;
}
