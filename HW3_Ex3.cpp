//Name: Nguyễn Thị Thu Uyên
//Student's ID: 22521643
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

bool searchOperation() {
    return rand() % 2 == 0; 
}

void exponentialBackoffSearch(int maxRetries, int baseDelay) {
    int attempt = 0;
    while (attempt < maxRetries) {
        if (searchOperation()) {
            cout << "Search successful on attempt " << attempt + 1 << endl;
            return;
        } else {
            cout << "Search failed on attempt " << attempt + 1 << ". Retrying..." << endl;
            int delay = baseDelay * (1 << attempt); 
            this_thread::sleep_for(chrono::milliseconds(delay));
            attempt++;
        }
    }
    cout << "Search failed after " << maxRetries << " attempts." << endl;
}

int main() {
    srand(time(0)); 

    int maxRetries = 5;
    int baseDelay = 100; 

    exponentialBackoffSearch(maxRetries, baseDelay);

    return 0;
}
