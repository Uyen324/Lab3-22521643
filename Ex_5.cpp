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

SearchResult linearSearch(int arr[], int n, int x) {
    auto start = high_resolution_clock::now();
    printTime("Linear Search starts at: ", start);
    int comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i] == x) {
            auto end = high_resolution_clock::now();
            printTime("Linear Search ends at: ", end);
            return {i, comparisons, end - start};
        }
    }
    auto end = high_resolution_clock::now();
    printTime("Linear Search ends at: ", end);
    return {-1, comparisons, end - start};
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

SearchResult jumpSearch(int arr[], int n, int x) {
    auto start = high_resolution_clock::now();
    printTime("Jump Search starts at: ", start);
    int comparisons = 0;
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n) - 1] < x) {
        comparisons++;
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            auto end = high_resolution_clock::now();
            printTime("Jump Search ends at: ", end);
            return {-1, comparisons, end - start};
        }
    }
    while (arr[prev] < x) {
        comparisons++;
        prev++;
        if (prev == min(step, n)) {
            auto end = high_resolution_clock::now();
            printTime("Jump Search ends at: ", end);
            return {-1, comparisons, end - start};
        }
    }
    comparisons++;
    if (arr[prev] == x) {
        auto end = high_resolution_clock::now();
        printTime("Jump Search ends at: ", end);
        return {prev, comparisons, end - start};
    }
    auto end = high_resolution_clock::now();
    printTime("Jump Search ends at: ", end);
    return {-1, comparisons, end - start};
}


int main() {
   int arr[100];
    int n;
    inputArray(arr, n);
    int x;
    cout << "Enter X: ";
    cin >> x;

    SearchResult linearResult, binaryResult, jumpResult;

    thread linearThread([&]() { linearResult = linearSearch(arr, n, x); });
    thread binaryThread([&]() { binaryResult = binarySearch(arr, 0, n - 1, x); });
    thread jumpThread([&]() { jumpResult = jumpSearch(arr, n, x); });

    linearThread.join();
    binaryThread.join();
    jumpThread.join();

    cout << "Linear Search: Index = " << linearResult.index << ", Comparisons = " 
         << linearResult.comparisons << ", Duration = " << linearResult.timeTaken.count() << " seconds" << endl;
    cout << "Binary Search: Index = " << binaryResult.index << ", Comparisons = " 
         << binaryResult.comparisons << ", Duration = " << binaryResult.timeTaken.count() << " seconds" << endl;
    cout << "Jump Search: Index = " << jumpResult.index << ", Comparisons = " 
         << jumpResult.comparisons << ", Duration = " << jumpResult.timeTaken.count() << " seconds" << endl;
    return 0;
}
