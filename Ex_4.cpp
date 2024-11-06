#include <iostream>
#include <algorithm>
using namespace std;

int binarySearch(const int arr[], int n) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        
        if (arr[mid] == mid) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}
int findMissing(int arr[], int n) {
    sort(arr, arr + n);  
    return binarySearch(arr, n);
}
int main() {
    int n;
    cout << "Enter the size of the array (n): ";
    cin >> n;
    int arr[n];
    cout << "Enter numbers from 0 to " << n << ": ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    int missing = findMissing(arr, n);
    cout << "The missing number is: " << missing << endl;
    return 0;
}
