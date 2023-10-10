// 二叉搜索树 

#include "./avl.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

void test() {
    
    AVL_Tree<int, string> root;

    // 根据定义 高度为h的二叉树最多能容纳2^h-1个元素
    // 那么正确的表现是，当插入s1个数字时，树的高度为h1
    // 再插入任意一个数字，树的高度则变为h1+1
    int h1 = 10, s1 = pow(2, h1)-1; 
    int h2 = 12, s2 = pow(2, h2)-1;

    // 插入s2个数据 检查高度是否达到预期
    vector<int> vec(s2);
    generate(vec.begin(), vec.end(), [] () { static int i = 0; return ++i; });
    for (auto i : vec2) { root.insert(i, to_string(i)); }

    cout << "root.size: " << root.size() << endl;
    cout << "root.height: " << root.height() << endl;

    // 删除s2-s1个数据 检查高度是否达到预期
    for (int i = s1+1; i <= s2; i++) { root.remove(i); }

    cout << "root.size: " << root.size() << endl;
    cout << "root.height: " << root.height() << endl;

    /*  result:
        root.size: 4095
        root.height: 12
        root.size: 1023
        root.height: 10
        结果符合预期
    */
}

int main() {
    test();
}
