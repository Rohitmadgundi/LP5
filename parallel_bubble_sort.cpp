#include <iostream>
#include <vector>
#include <omp.h>

// Function to perform bubble sort on a given range of the vector
void bubbleSortRange(std::vector<int>& arr, int start, int end) {
    for (int i = start; i <= end; ++i) {
        for (int j = start; j < end - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform parallel bubble sort
void parallelBubbleSort(std::vector<int>& arr) {
    int size = arr.size();
    bool sorted = false;

    // Parallel bubble sort until the array is sorted
    while (!sorted) {
        sorted = true;

        #pragma omp parallel for
        for (int i = 0; i < size - 1; i += 2) {
            bubbleSortRange(arr, i, i + 1);
        }

        #pragma omp parallel for
        for (int i = 0; i < size - 1; ++i) {
            // Check if sorting is still required
            if (arr[i] > arr[i + 1]) {
                sorted = false;
            }
        }
    }
}

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    parallelBubbleSort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
