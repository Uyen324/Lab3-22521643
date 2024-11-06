#include <iostream>
#include <algorithm>
using namespace std;

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}
int quickSelect(int arr[], int left, int right, int k) {
    if (left == right) return arr[left];

    int pivot_idx = partition(arr, left, right);

    if (k == pivot_idx) {
        return arr[k];
    } else if (k < pivot_idx) {
        return quickSelect(arr, left, pivot_idx - 1, k);
    } else {
        return quickSelect(arr, pivot_idx + 1, right, k);
    }
}
int findKthSmallest(int arr[], int n, int k) {
    if (k > 0 && k <= n) {
        return quickSelect(arr, 0, n - 1, k - 1); 
    }
    return -1;
}
int main() {
    int n, k;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    int arr[n];
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Enter the k th : ";
    cin >> k;
    int kthSmallest = findKthSmallest(arr, n, k);
    if (kthSmallest != -1) {
        cout << "The " << k << "th smallest element is: " << kthSmallest << endl;
    } else {
        cout << "Invalid k value" << endl;
    }
    return 0;
}
