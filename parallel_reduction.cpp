#include <iostream>
#include <vector>
#include <omp.h>

// Function to calculate the minimum value using parallel reduction
int parallelMin(const std::vector<int>& arr) {
    int size = arr.size();
    int result = arr[0];

    #pragma omp parallel for reduction(min : result)
    for (int i = 1; i < size; ++i) {
        if (arr[i] < result) {
            result = arr[i];
        }
    }

    return result;
}

// Function to calculate the maximum value using parallel reduction
int parallelMax(const std::vector<int>& arr) {
    int size = arr.size();
    int result = arr[0];

    #pragma omp parallel for reduction(max : result)
    for (int i = 1; i < size; ++i) {
        if (arr[i] > result) {
            result = arr[i];
        }
    }

    return result;
}

// Function to calculate the sum using parallel reduction
int parallelSum(const std::vector<int>& arr) {
    int size = arr.size();
    int result = 0;

    #pragma omp parallel for reduction(+: result)
    for (int i = 0; i < size; ++i) {
        // std::cout << omp_get_team_num();
        result += arr[i];
    }

    return result;
}

// Function to calculate the average using parallel reduction
double parallelAverage(const std::vector<int>& arr) {
    int size = arr.size();
    int sum = parallelSum(arr);

    return static_cast<double>(sum) / size;
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

    int minVal = parallelMin(arr);
    int maxVal = parallelMax(arr);
    int sum = parallelSum(arr);
    double avg = parallelAverage(arr);

    std::cout << "Minimum value: " << minVal << std::endl;
    std::cout << "Maximum value: " << maxVal << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << avg << std::endl;

    return 0;
}
