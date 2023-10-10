// 堆排序 之 最大堆排序
#include "heap_sort.h"

#include <cstddef> // for size_t
#include <algorithm>

// 维护堆性质
// 父节点大于左右子节点
template<typename _Tp>
static void max_heapify(_Tp* arr, size_t n, size_t max) {
    
    // 合法性检查
    if(n > max) {
        return;
    }

    // 找子节点
    int l = n * 2 + 1;
    int r = l + 1;

    // 找最大值
    // 若是最小堆排序 则在此改为寻找最小值即可
    int largest = (l < max && arr[l] > arr[n]) ? l : n;
    if(r < max && arr[r] > arr[largest]) {
        largest = r;
    }

    if(largest == n) {
        return;
    }

    // 使父节点最大
    // swap(arr[n], arr[largest]);
    auto t = arr[n];
    arr[n] = arr[largest];
    arr[largest] = t;

    // 检查交换是否影响祖父节点
    max_heapify(arr, largest, max);
}

// 建堆
// 利用f1 逆序遍历数组前半段
template<typename _Tp>
void max_heap_build(_Tp* arr, size_t max) {
    for(int i = max / 2; i >= 0; i--) {
        max_heapify(arr, i, max);
    }
}

// 堆排序
// 对数组每个位置依次建堆 即可完成类似于选择排序的操作
// 相较于选择排序，堆排序是渐进最优的
template<typename _Tp>
void max_heap_sort(_Tp* arr, size_t max) {
    for(int i = 0; i < max; i++) {
        max_heap_build(arr+i, max-i);
    }
}
