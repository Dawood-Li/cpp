#include "list.h"

// 创建
List* init() {
    return new List;
}

// 头插
void push_front(List* list, void *data) {
    list->head = new Node { .data = data, .next = list->head };
    if(list->tail == nullptr) {
        list->tail = list->head;
    }
    list->size++;
}

// 尾插
void push_back(List* list, void *data) {
    list->tail = list->tail->next = new Node{ .data = data };
    if(list->head == nullptr) {
        list->head = list->tail;
    }
    list->size++;
}

// 头部
void* front(List* list) {
    return (list->head == nullptr) ? nullptr : list->head->data;
}

// 头删
void* pop_front(List* list) {

    // 如果头部为空 即链表为空
    if(list->head == nullptr) {
        return nullptr;
    }

    void *data = list->head->data;

    // 如果头部不为空 且 尾部==头部
    if(list->tail == list->head) {
        delete list->head;
        delete list->tail;
        list->head = nullptr;
        list->tail = nullptr;
    }

    // 若头部不为空 且尾部 != 头部
    else {
        Node *node = list->head;
        list->head = list->head->next;
        delete node;
    }

    list->size--;
    
    return data;
}

// 查找
void* find_if(List *list, bool (*f)(void*, void*), void *args) {
    for(Node* node = list->head; node != nullptr; node = node->next) {
        if(f(node->data, args)) {
            return node->data;
        }
    }
    return nullptr;
}

// 查找
void* find_if(List *list, bool (*f)(void*, void*), void *args) {
    for(Node* node = list->head; node != nullptr; node = node->next) {
        if(f(node->data, args)) {
            return node->data;
        }
    }
    return nullptr;
}

/*
example:

int value = 1;

bool find(void *data, void *args = nullptr) {
    return (*(int*)data == *(int*)args);
}

void* data = find_if(list, find, &value);
if(data != nullptr) {
    cout << *(int*)data << endl;
}

*/
