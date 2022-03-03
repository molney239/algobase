#ifndef ALGOBASE_TREAP_H
#define ALGOBASE_TREAP_H

namespace treap {

    template<typename T>
    struct node {

        node(T x, unsigned long long y) {
            this->x = x;
            this->y = y;
            this->left = nullptr;
            this->right = nullptr;
        }

        T x;
        unsigned long long y;

        node<T>* left;
        node<T>* right;

    };

    template<typename T>
    node<T>* merge(node<T>* a, node<T>* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a->y > b->y) {
            a->right = merge(a->right, b);
            return a;
        } else {
            b->left = merge(a, b->left);
            return b;
        }
    }

    template<typename T>
    std::pair<node<T>*, node<T>*> split(node<T>* a, T value) {
        if (a == nullptr) return std::pair<node<T>*, node<T>*>(nullptr, nullptr);
        if (a->x < value) {
            auto p = split(a->right, value);
            a->right = p.first;
            return std::pair<node<T>*, node<T>*>(a, p.second);
        } else {
            auto p = split(a->left, value);
            a->left = p.second;
            return std::pair<node<T>*, node<T>*>(p.first, a);
        }
    }

    template<typename T>
    node<T>* min(node<T>* a) {
        if (a == nullptr) return nullptr;
        if (a->left == nullptr) return a;
        return min(a->left);
    }

    template<typename T>
    node<T>* insert(node<T>* a, node<T>* new_node) {
        if (new_node == nullptr) return a;
        if (a == nullptr) return new_node;

        auto p = split(a, new_node->x);
        if (p.second != nullptr && min(p.second)->x == new_node->x) {
            a = merge(p.first, p.second);
        } else a = merge(p.first, merge(new_node, p.second));
        return a;
    }

    template<typename T>
    node<T>* search(node<T>* a, T value) {
        if (a == nullptr) return nullptr;
        if (a->x == value) return a;
        if (a->x < value) return search(a->right, value);
        else return search(a->left, value);
    }

    template<typename T>
    node<T>* remove(node<T>* a, T x) {
        if (a == nullptr) return nullptr;
        auto p = split(a, x);
        p.second = split(p.second, x + 1).second;
        a = merge(p.first, p.second);
        return a;
    }

}

#endif //ALGOBASE_TREAP_H