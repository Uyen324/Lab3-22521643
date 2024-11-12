#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include <ctime>

using namespace std;
using namespace std::chrono;

struct SearchResult {
    int index;
    int comparisons;
    duration<double> timeTaken;
};

void inputArray(int arr[], int &n) {
    cout << "Enter the size of the array (e.g., 100): ";
    cin >> n;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
}

void printTime(const string &message, const time_point<high_resolution_clock> &timePoint) {
    auto time_t_format = system_clock::to_time_t(timePoint);
    cout << message << ctime(&time_t_format);
}

SearchResult binarySearch(int arr[], int left, int right, int x) {
    auto start = high_resolution_clock::now();
    printTime("Binary Search starts at: ", start);
    int comparisons = 0;
    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;
        if (arr[mid] == x) {
            auto end = high_resolution_clock::now();
            printTime("Binary Search ends at: ", end);
            return {mid, comparisons, end - start};
        }
        if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    auto end = high_resolution_clock::now();
    printTime("Binary Search ends at: ", end);
    return {-1, comparisons, end - start};
}

SearchResult bidirectionalBinarySearch(int arr[], int n, int x) {
    auto start = high_resolution_clock::now();
    printTime("Bidirectional Binary Search starts at: ", start);
    int left = 0, right = n - 1;
    int comparisons = 0;
    while (left <= right) {
        comparisons++;
        int midLeft = left + (right - left) / 2;
        int midRight = right - (right - left) / 2;
        if (arr[midLeft] == x) {
            auto end = high_resolution_clock::now();
            printTime("Bidirectional Binary Search ends at: ", end);
            return {midLeft, comparisons, end - start};
        }
        if (arr[midRight] == x) {
            auto end = high_resolution_clock::now();
            printTime("Bidirectional Binary Search ends at: ", end);
            return {midRight, comparisons, end - start};
        }
        if (arr[midLeft] < x) {
            left = midLeft + 1;
        } else {
            right = midLeft - 1;
        }
        if (arr[midRight] > x) {
            right = midRight - 1;
        } else {
            left = midRight + 1;
        }
    }
    auto end = high_resolution_clock::now();
    printTime("Bidirectional Binary Search ends at: ", end);
    return {-1, comparisons, end - start};
}

int main() {
      int arr[100];
    int n;
    inputArray(arr, n);
    int x;
    cout << "Enter X: ";
    cin >> x;
    SearchResult bidirectionalResult = bidirectionalBinarySearch(arr, n, x);
    SearchResult traditionalResult = binarySearch(arr, 0, n - 1, x);

    cout << "Bidirectional Binary Search: Index = " << bidirectionalResult.index 
         << ", Comparisons = " << bidirectionalResult.comparisons 
         << ", Duration = " << bidirectionalResult.timeTaken.count() << " seconds" << endl;
    cout << "Traditional Binary Search: Index = " << traditionalResult.index 
         << ", Comparisons = " << traditionalResult.comparisons 
         << ", Duration = " << traditionalResult.timeTaken.count() << " seconds" << endl;
    return 0;
}
