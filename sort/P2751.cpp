// N이 1이상 10e7이하
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

using namespace std;

int N;
vector<int> numbers;

void getInput() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }
}

// heap sort
void heapSort() {
    priority_queue<int, vector<int>, greater<int> > pq;
    for (const auto& number: numbers) {
        pq.push(number);
    }

    numbers.clear();
    while (!pq.empty() ) {
        numbers.push_back(pq.top());
        pq.pop();
    }
}

/* 
  quick sort
  : be accomplished by dividing the array into two partitions and then sort each partition recursively.
  
  ** Pivot **
  The array is partitioned by placing all items smaller than some pibot item before
  and all items larger than the pibot item after it. The pivot item can be any item.

  [Pseudo-code]
  void quicksort (index low, index high)
  {
    index pivotpoint;

    if (high > low) {
      partition(low, high, pivotpoint);
      quicksort(low, pivotpoint - 1);
      quicksort(pivotpoint + 1, high); 
    }
  }

  [Time complexity]
  average: O(nlogn)
  worst: O(n^2)
*/
void partition(int low, int high, int& pivot) {
    int pivotItem = numbers[low];
    int temp, i, j = low;

    for (i = low + 1; i <= high; i++) {
      if (numbers[i] < pivotItem) {
          j++;
          SWAP(numbers[i], numbers[j], temp);
      }
    }
    pivot = j;
    SWAP(numbers[low], numbers[pivot], temp); 
    
}

void quickSort(int low, int high) {
    int pivot;

    if (high > low) {
      partition(low, high, pivot);
      quickSort(low, pivot-1);
      quickSort(pivot+1, high);
    }
}

/*
  merge sort
  : combining two sorted arrays into one sorted array.
  
  1) Divide the array into two subarrays each with n/2 items.
  2) Conquer (solve) ech subarray by sorting it. Unless the array is sufficiently
     small, use recursion to do this.
  3) Combine the solutions to the subarrays by merging them into a single sorted array.

  [Pseudo-code]
  void mergesort (int n, keytype S[])
  {
    if (n>1) {
      const int h = n/2, m = n - h;
      keytype U[1..h], V[1..m];
      copy S[1] through S[h] to U[1] through U[h];
      copy S[h+1] through S[n] to V[1] through V[m];
      mergesort(h, U);
      mergesort(m, V);
      merge(h, m, U, V, S);
    }
  }
*/
void merge(int left, int mid, int right) {
    int i, j;
    i = left;
    j = mid + 1;
    vector<int> sorted;

    while(i <= mid && j <= right) {
        if (numbers[i] < numbers[j]) {
            sorted.push_back(numbers[i++]);
        } 
        else {
            sorted.push_back(numbers[j++]);
        }
    }

    if (i > mid) {
        for (int l = j; l <= right; l++) {
            sorted.push_back(numbers[l]);
        }
    }
    else {
        for (int l = i; l <= mid; l++) {
            sorted.push_back(numbers[l]);
        }
    }

    for (int l = left; l <= right; l++) {
        numbers[l] = sorted[l - left];
    }
}

void mergeSort(int left, int right) {
    int mid = (left + right) / 2;

    if (left < right) {
        mergeSort(left, mid);
        mergeSort(mid+1, right);
        merge(left, mid, right);
    }
}

void print() {
    for (const auto& number:numbers) {
        cout << number << "\n";
    }
}

int main() {
    getInput();
    mergeSort(0, numbers.size()-1);
    print();
}