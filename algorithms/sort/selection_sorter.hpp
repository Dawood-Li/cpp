#pragma once
#include "./sorter_base.hpp"

template <class T>
class Selection_Sorter : public Sorter_Base<T> {  
protected:
    void _sort(std::vector<T>& arr, const std::function<bool(const T&,const T&)>& comp) override {
        for(int i = 0; i < arr.size()-1; i++) {  
            int min_index = i;  
            for(int j = i + 1; j < arr.size(); j++) {
                if(comp(arr[j], arr[min_index])) {  
                    min_index = j;
                }  
            }  
            std::swap(arr[i], arr[min_index]);
        }  
    }
};
