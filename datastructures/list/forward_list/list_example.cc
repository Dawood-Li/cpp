#include "list.h"

#include <iostream>
using namespace std;

int value = 1;
bool find(void *data, void *args = nullptr) {
    return (*(int*)data == *(int*)args);
}

int main() {

    auto list = init();

    // 头插
    push_front(list, new int(1));
    push_front(list, new int(2));
    push_front(list, new int(3));
    push_front(list, new int(4));

    cout << "size: " << list->size << endl;

    // 尾插
    push_back(list, new int(1));
    push_back(list, new int(2));
    push_back(list, new int(3));
    push_back(list, new int(4));

    cout << "size: " << list->size << endl;

    // 弹出
    for(int i = 0; i < 4; i++) {
        cout << *(int*)pop_front(list) << endl;
    }

    cout << "size: " << list->size << endl;

    // 遍历
    for(Node* node = list->head; node != nullptr; node = node->next) {
        cout << *(int*)node->data << endl;
    }

    // 查找
    for(int i = -3; i <= 4; i++) {

        void* data = find_if(list, find, &i);
        if(data != nullptr) {
            cout << *(int*)data << endl;
        } else {
            cout << "nullptr" << endl;
        }
    }

    return 0;
}
