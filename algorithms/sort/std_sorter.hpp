#pragma once
#include "./sorter_base.hpp"

template <class T>
class Std_Sorter : public Sorter_Base<T> {
protected:
    void _sort(std::vector<T>& arr, const std::function<bool(const T&,const T&)>& comp) override {
        std::sort(arr.begin(), arr.end(), comp);
    }
};
