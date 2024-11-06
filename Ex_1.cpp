#include <iostream>
using namespace std;
int binarySearch(int A[], int n, int x) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (x == A[m]) return m;
        if (x < A[m]) r = m - 1;
        else l = m + 1;
    }
    return -1;
}
int findFirst(int A[], int n, int x) {
    int pos = binarySearch(A, n, x);
    if (pos == -1) return -1;  

    while (pos > 0 && A[pos - 1] == x) {
        pos--;
    }
    return pos;
}
int findLast(int A[], int n, int x) {
    int pos = binarySearch(A, n, x);
    if (pos == -1) return -1;  

    while (pos < n - 1 && A[pos + 1] == x) {
        pos++;
    }
    return pos;
}
int countOccurrences(int A[], int n, int x) {
    int first = findFirst(A, n, x);
    if (first == -1) return 0;  // 

    int last = findLast(A, n, x);
    return last - first + 1;
}
int main() {
    int n, x;
    cout << "Enter the number of elements: ";
    cin >> n;
    int A[n];
    cout << "Enter sorted elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    cout << "Enter the target value: ";
    cin >> x;
    int count = countOccurrences(A, n, x);
    cout << "The count of " << x << " is: " << count << endl;
    return 0;
}
