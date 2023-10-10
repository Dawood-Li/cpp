#pragma once
#include "./sorter_base.hpp"

template <class T>
class Insertion_Sorter : public Sorter_Base<T> {  
protected:
    void _sort(std::vector<T>& arr, const std::function<bool(const T&,const T&)>& comp) override {
        for (int i, j = 1; j < arr.size(); ++j) {  
            T key = arr[j];  
            for (i = j-1; i >= 0 && comp(key, arr[i]); --i) {  
                arr[i + 1] = arr[i];  
            }  
            arr[i + 1] = key;  
        }  
    }  
};  
