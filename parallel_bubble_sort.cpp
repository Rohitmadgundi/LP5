#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;

    for (int i = 0; i < n - 1 && swapped; i++) {
        swapped = false;

        // Even iteration
#pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // Odd iteration
#pragma omp parallel for shared(arr, swapped)
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    bubbleSort(arr);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

// In this modified code, the bubble sort algorithm is divided into even and odd iterations. In each iteration, even-indexed elements are compared and swapped in parallel, and then odd-indexed elements are compared and swapped in parallel. The loop terminates if no swaps are made in any iteration.

// The OpenMP parallel for directive is used for both the even and odd iterations, allowing multiple threads to work on different portions of the array simultaneously. The swapped flag is shared among the threads to track if any swap has occurred.

// Compile the code using the -fopenmp flag, as mentioned before, to enable OpenMP support.

// Note that the performance improvement from using even-odd iterations may vary depending on the input data and the number of available threads.




