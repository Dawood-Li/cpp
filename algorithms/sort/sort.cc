#include "./sorter_factory.hpp"
#include "../../utils/timer.h"
#include <iostream>  
#include <string>  
#include <vector>
#include <algorithm>
#include <chrono>
#include <memory>

template <class T>
void print(const std::vector<T>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    } std::cout << std::endl;
}

template <class T>
bool check(const std::vector<T>& arr, std::function<bool(const T&, const T&)> comp) {
    for (int i = 1; i < arr.size(); ++i) {
        if (! comp(arr[i-1], arr[i])) {
            return false;
        }
    }
    return true;
}

template <class T>
bool sorter_test(const std::vector<T>& arr, const std::string& sorter_name) {
    auto sorter = Sorter_Factory<T>::create(sorter_name);  
    std::vector<T> arr2;
    arr2 = arr;
    sorter->sort(arr2, false);
    if (check<T>(arr2, [] (const T&l, const T&r) { return l < r; }) == false) {
        std::cout << sorter_name << "check asc fail.\n";
        print(arr); print(arr2);
        return false;
    }
    sorter->sort(arr2, true);
    if (check<T>(arr2, [] (const T&l, const T&r) { return l > r; }) == false) {
        std::cout << sorter_name << "check desc fail.\n";
        print(arr); print(arr2);
        return false;
    }
    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> time_points;
    time_points.push_back(std::chrono::high_resolution_clock::now());
    sorter->sort(arr2);
    time_points.push_back(std::chrono::high_resolution_clock::now());
    sorter->sort(arr2, true);
    time_points.push_back(std::chrono::high_resolution_clock::now());
    sorter->sort(arr2, true);
    time_points.push_back(std::chrono::high_resolution_clock::now());
    auto d1 = std::chrono::duration_cast<std::chrono::nanoseconds>(time_points[1] - time_points[0]).count() / 1000000.0;
    auto d2 = std::chrono::duration_cast<std::chrono::nanoseconds>(time_points[2] - time_points[1]).count() / 1000000.0;
    auto d3 = std::chrono::duration_cast<std::chrono::nanoseconds>(time_points[3] - time_points[2]).count() / 1000000.0;
    auto avg = (d1 + d2 + d3) / 3.0;
    std::cout << sorter_name << ": " << std::endl;
    std::cout << "random  : " << d1 << " ms" << std::endl;
    std::cout << "worst   : " << d2 << " ms" << std::endl;
    std::cout << "best    : " << d3 << " ms" << std::endl;
    std::cout << "averange: " << avg << " ms" << std::endl;
    std::cout << std::endl;
    return true;
}

template <class T, size_t len>
void test() {
    std::vector<T> arr(len);
    for(int i = 0; i < arr.size(); i++) {
        arr[i] = i;
    }
    random_shuffle(arr.begin(), arr.end());

    sorter_test(arr, "Std");
    sorter_test(arr, "Bubble");
    sorter_test(arr, "Selection");
    sorter_test(arr, "Insertion");
    sorter_test(arr, "Quic");
    sorter_test(arr, "Quic_Non_Recursive");
}

int main() {    
    test<float, 50>();
}
