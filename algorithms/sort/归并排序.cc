#include <iostream>
#include <vector>
#include <limits>
using namespace std;

void merge_sort(vector<int> &arr, int front, int end) {
    
    if(front >= end) {
        return;
    }

    int mid = (front + end) / 2;
    merge_sort(arr, front, mid);
    merge_sort(arr, mid +1, end);

    vector<int> larr(arr.begin() + front, arr.begin() + mid + 1);
    vector<int> rarr(arr.begin() + mid + 1, arr.begin() + end + 1);

    int lindex = 0;
    int rindex = 0;

    larr.push_back(numeric_limits<int>::max());
    rarr.push_back(numeric_limits<int>::max());

    for(int i = front; i <= end; i++) {
        arr[i] = larr[lindex] < rarr[rindex] ? larr[lindex++] : rarr[rindex++];
    }
}

int main() {

    vector<int> arr { 50, 21, 28, 65, 39, 59, 56, 22, 95, 12, 90, 53, 32, 77, 33 };

    merge_sort(arr, 0, 14);

    for(auto a : arr) {
        cout << a << " ";
    }
    cout << endl;
}
