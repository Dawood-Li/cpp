#pragma once

struct Node {
    void *data = nullptr;
    Node *next = nullptr;
};

struct List {
    Node *head = nullptr;
    Node *tail = nullptr;
    unsigned size = 0;
};

// 创建
List* init();

// 头插
void push_front(List* list, void *data);

// 尾插
void push_back(List* list, void *data);

// 头删
void* pop_front(List* list);

// 查找
void* find_if(List *list, bool (*f)(void *data, void *args), void* args = nullptr);

