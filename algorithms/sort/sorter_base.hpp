#pragma once
#include <vector>
#include <functional>

template <class T>
class Sorter_Base {
public:
    void sort(std::vector<T>& arr, bool DESC=false) {
        DESC ? _sort(arr, [] (const T&l, const T&r) { return l > r; })
             : _sort(arr, [] (const T&l, const T&r) { return l < r; });
    }
protected:
    virtual void _sort(std::vector<T>& arr, const std::function<bool(const T&, const T&)>& comp) = 0;
};
