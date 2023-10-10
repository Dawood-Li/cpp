#pragma once
#include "./sorter_base.hpp"

template <class T>
class Bubble_Sorter : public Sorter_Base<T> {  
protected:
    void _sort(std::vector<T>& arr, const std::function<bool(const T&,const T&)>& comp) override {
        for (int i = 0; i < arr.size(); i++) {  
            for (int j = 0; j < arr.size() - i - 1; j++) {
                if (comp(arr[j+1], arr[j])) {  
                    std::swap(arr[j], arr[j+1]);  
                }  
            }  
        }  
    }
};
