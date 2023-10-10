#pragma once  
#include "./sorter_base.hpp"  
#include <stack>

template <class T>  
class Quick_Non_Recursive_Sorter : public Sorter_Base<T> {  
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

    void quicksort(std::vector<T>& arr, int left, int right, const std::function<bool(const T&, const T&)>& comp) {
        std::stack<int> st;  
        st.push(left);  
        st.push(right); 
        while (!st.empty()) {  
            int end   = st.top(); st.pop();
            int begin = st.top(); st.pop();
            int key = partition(arr, begin, end, comp);
            if (end   > key  ) { st.push(key+1); st.push(end); }
            if (begin < key-1) { st.push(begin); st.push(key); }  
        }
    }
};
