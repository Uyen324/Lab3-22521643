#include <iostream>
#include <cmath>
using namespace std;
int jumpSearch(int arr[], int n, int target, int step) {
    int i = 0;
    int m = step; 
    while (m < n && arr[m] < target) {
        i = m;              
        m += step;          
        if (m >= n) m = n;  
       
        if (arr[m - 1] < target) {
            step = sqrt(step); 
        }
    }
    for (int x = i; x < m; x++) {
        if (arr[x] == target) 
            return x; 
    }

    return -1; 
}
int main() {
    int n, target, step;
    cout << "Enter number of elements: ";
    cin >> n;
    int arr[n];
    cout << "Enter sorted elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout << "Enter target value: ";
    cin >> target;
    cout << "Enter initial step size: ";
    cin >> step;

    int result = jumpSearch(arr, n, target, step);
    if (result != -1)
        cout << "Element found at index " << result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
