#include <iostream>
#include <string>
using namespace std;

int interpolationSearch(string arr[], int n, const string& target) {
    int lo = 0, hi = n - 1;
    while (lo <= hi && target >= arr[lo] && target <= arr[hi]) {
        if (lo == hi) {
            if (arr[lo] == target) return lo;
            return -1;
        }
        int pos = lo + ((target.compare(arr[lo]) * (hi - lo)) / 
                        (arr[hi].compare(arr[lo])));
        if (pos < lo || pos > hi)
            return -1;
        if (arr[pos] == target) 
            return pos;
        if (arr[pos] < target)
            lo = pos + 1;
        else
            hi = pos - 1;
    }
    return -1; 
}
int main() {
    int n;
    cout << "Enter the number of strings: ";
    cin >> n;
    string arr[n];
    cout << "Enter sorted strings: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    string target;
    cout << "Enter the target string: ";
    cin >> target;
    int result = interpolationSearch(arr, n, target);
    if (result != -1)
        cout << "String found at index " << result << endl;
    else
        cout << "String not found" << endl;

    return 0;
}
