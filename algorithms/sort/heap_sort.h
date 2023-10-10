// 堆排序 之 最大堆排序
#pragma once
#include <cstddef> // for size_t

// 建最大堆
template<typename _Tp>
void max_heap_build(_Tp* arr, size_t max);

// 最大堆排序
// 对数组每个位置依次建堆 即可完成类似于选择排序的操作
// 相较于选择排序，堆排序是渐进最优的
template<typename _Tp>
void max_heap_sort(_Tp* arr, size_t max);
