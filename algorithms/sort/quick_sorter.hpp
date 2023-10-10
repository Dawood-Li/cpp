#pragma once  
#include "./sorter_base.hpp"  

// https://leetcode.cn/circle/discuss/kiHnKs/

template <class T>  
class Quick_Sorter : public Sorter_Base<T> {  
protected:  
    void _sort(std::vector<T>& arr, const std::function<bool(const T&, const T&)>& comp) override {  
        quicksort(arr, 0, arr.size()-1, comp);
    } 

private:

    int partition(std::vector<T>& arr, int l, int r, const std::function<bool(const T&, const T&)>& comp) {
        int i = l, j = r;
        while (i < j) {
            while (i < j && comp(arr[l], arr[j])) j--;  
            while (i < j && comp(arr[l], arr[i])) i++;
            std::swap(arr[i], arr[j]);
        }
        std::swap(arr[i], arr[l]);
        return i;
    }

    void quicksort(std::vector<T>& arr, int l, int r, const std::function<bool(const T&, const T&)>& comp) {
        if (l >= r) { return; };
        int i = partition(arr, l, r, comp);
        quicksort(arr, l, i - 1, comp);
        quicksort(arr, i + 1, r, comp);
        // 以下是为了节约栈空间的实现
        // while (l < r) {
            // int i = partition(arr, l, r, comp);
            // if (i - l < r - i) {
                // quicksort(arr, l, i - 1, comp);
                // l = i + 1;
            // } else {
                // quicksort(arr, i + 1, r, comp);
                // r = i - 1;
            // }
        // }
    }
};
