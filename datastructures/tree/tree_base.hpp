#pragma once

/*
    binary search tree:
        implement by the recursion method.
    
    Can only be used for counting or sorting.
    
    the performance is not good.
    but at least better than ordered linked list.
    and it can derive the AVL tree.

    might include a new interface function:
        next
*/

#include <functional> // for traversal
                      // a function will be passed from outside
                      // and then used to operate all elements

#include <queue>      // for breadth first traversal

template<typename _Tp_k, typename _Tp_v>
class Tree_Base {

public:
    
    Tree_Base() {}
    ~Tree_Base() { destory(); }

    // insret and modify
    void insert(_Tp_k key, _Tp_v value) { _insert(root, key, value); }
    
    auto find(_Tp_k key) const -> const _Tp_v* { return _find(root, key); }

    int height() const { return _height(root); }

    int size() const { return _size(root); }

    auto min() const -> const _Tp_v* {
        if (root == nullptr) { return nullptr; }
        for (auto *p = root; ; p = p->l) { if (p->l == nullptr) { return &p->v; } }
    }

    auto max() const -> const _Tp_v* {
        if (root == nullptr) { return nullptr; }
        for (auto *p = root; ; p = p->r) { if (p->r == nullptr) { return &p->v; } }
    }

    void remove(_Tp_k key) { _remove(root, key); };

    void destory() { _destory(root); }

    void preorder_traversal(std::function<void(const _Tp_v&)> func) {
        _preorder_traversal(root, func);
    }

    void inorder_traversal(std::function<void(const _Tp_v&)> func) {
        _inorder_traversal(root, func);
    }

    void postorder_traversal(std::function<void(const _Tp_v&)> func) {
        _postorder_traversal(root, func);
    }

    void breadth_first_traversal(std::function<void(const _Tp_v&)> func) {
        _breadth_first_traversal(root, func);
    }

protected:

    struct _tree_node {
        _Tp_k k;                 // key
        _Tp_v v;                 // value
        _tree_node *l = nullptr; // left
        _tree_node *r = nullptr; // right
    } *root = nullptr;

    // insert and modify
    virtual void _insert(_tree_node *&node, _Tp_k key, _Tp_v value) {
        if (node == nullptr) {
            node = new _tree_node { key, value };
        } else if (key == node->k) {
            node->v = value;
        } else if (key < node->k) {
            _insert(node->l, key, value);
        } else { // (key > node->k)
            _insert(node->r, key, value);
        }
    }

    int _height(_tree_node *node) const {
        auto max = [] (auto a, auto b) { return a > b ? a : b; };
        return node == nullptr ? 0 : max(_height(node->l), _height(node->r)) + 1;
    }

    int _size(_tree_node *node) const {
        return node == nullptr ? 0 : 1 + _size(node->l) + _size(node->r);
    }

    auto _find(_tree_node *node, _Tp_k key) const -> const _Tp_v* {
        if (node == nullptr) { return nullptr; }
        else if (key == node->k) { return &node->v; }
        else if (key <  node->k) { return _find(node->l, key); }
        else /* (key > node->k)*/{ return _find(node->r, key); }
    }

    virtual void _remove(_tree_node *& node, _Tp_k key) {
        if (node == nullptr) { return; }
        else if (key < node->k) { _remove(node->l, key); }
        else if (key > node->k) { _remove(node->r, key); }
        else { // key == node->k
            if (node->l == nullptr && node->r == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->l != nullptr && node->r == nullptr) {
                auto* p = node->l;
                delete node;
                node = p;
            } else if (node->l == nullptr && node->r != nullptr) {
                auto* p = node->r;
                delete node;
                node = p;
            } else {
                auto* p = node->r;
                while (p->l != nullptr) {
                    p = p->l;
                }
                node->k = p->k;
                node->v = p->v;
                _remove(node->r, p->k);
            }
        }
    }

    void _destory(_tree_node *&node) {
        if (node == nullptr) { return; }
        if (node->l != nullptr) { _destory(node->l); }
        if (node->r != nullptr) { _destory(node->r); }
        delete node; node = nullptr;
    }

    void _preorder_traversal(_tree_node *node, std::function<void(const _Tp_v&)> func) {
        if (node == nullptr) { return; }
        if (node->l != nullptr) { _preorder_traversal(node->l, func); }
        func(node->v);
        if (node->r != nullptr) { _preorder_traversal(node->r, func); }
    }

    void _inorder_traversal(_tree_node *node, std::function<void(const _Tp_v&)> func) {
        if (node == nullptr) { return; }
        func(node->v);
        if (node->l != nullptr) { _inorder_traversal(node->l, func); }
        if (node->r != nullptr) { _inorder_traversal(node->r, func); }
    }

    void _postorder_traversal(_tree_node *node, std::function<void(const _Tp_v&)> func) {
        if (node == nullptr) { return; }
        if (node->r != nullptr) { _postorder_traversal(node->r, func); }
        func(node->v);
        if (node->l != nullptr) { _postorder_traversal(node->l, func); }
    }

    void _breadth_first_traversal(_tree_node *node, std::function<void(const _Tp_v&)> func) {
        std::queue<_tree_node*> q;
        q.push(node);
        while (!q.empty()) {
            auto* p = q.front(); q.pop();
            func(p->v);
            if (p->l != nullptr) { q.push(p->l); }
            if (p->r != nullptr) { q.push(p->r); }
        }
    }
};
