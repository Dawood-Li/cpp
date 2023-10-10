#pragma once

/*
    avl tree:
        an self-balancing binary search tree.

    override:
        insert
        remove
*/

#include "../tree_base.hpp"
#include <iostream>
using namespace std;

template<typename _Tp_k, typename _Tp_v>
class AVL_Tree: public Tree_Base<_Tp_k, _Tp_v> {

protected:

    using _tree_node = typename Tree_Base<_Tp_k, _Tp_v>::_tree_node;

    void _left_rotate(_tree_node *&node) {
        auto* new_root = node->r;
        node->r = new_root->l;
        new_root->l = node;
        node = new_root;
    }

    void _right_rotate(_tree_node *&node) {
        auto* new_root = node->l;
        node->l = new_root->r;
        new_root->r = node;
        node = new_root;
    }

    int _balance(_tree_node *&node) const {
        return node == nullptr ? 0 :
            Tree_Base<_Tp_k, _Tp_v>::_height(node->l) -
            Tree_Base<_Tp_k, _Tp_v>::_height(node->r);
    }

    void _insert(_tree_node *&node, _Tp_k key, _Tp_v value) {
        if (node == nullptr) {
            node = new _tree_node { key, value, nullptr, nullptr };
            return;
        } else if (key == node->k) {
            node->v = value;
        } else if (key < node->k) {
            _insert(node->l, key, value);
        } else {
            _insert(node->r, key, value);
        }
        auto balance = _balance(node);
        if (balance < -1 || balance > 1) {
            if (key < node->k) {
                if (key < node->l->k) { // LL
                    _right_rotate(node);
                } else {                // LR
                    _left_rotate(node->l);
                    _right_rotate(node);
                }
            } else {
                if (key > node->r->k) { // RR
                    _left_rotate(node);
                } else {                // RL
                    _right_rotate(node->r);
                    _left_rotate(node);
                }
            }
        }
    }

    void _remove(_tree_node *&node, _Tp_k key) {
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
        if (_balance(node) == 2) {
            if (_balance(node->l) == 1) {       // LL
                _right_rotate(node);
            }
            else if (_balance(node->l) == -1) { // LR
                _left_rotate(node->l);
                _right_rotate(node);
            }
        }
        else if (_balance(node) == -2) {
            if (_balance(node->r) == 1) {       // RL
                _left_rotate(node);
            }
            else if (_balance(node->r) == -1) { // RR
                _right_rotate(node->r);
                _left_rotate(node);
            }
        }
    }
};
