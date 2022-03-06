#ifndef ALGOBASE_TREAP_H
#define ALGOBASE_TREAP_H

namespace treap {

    template<typename T>
    struct node {

        node(T x, unsigned long long y) {
            this->x = x;
            this->y = y;
            left = nullptr;
            right = nullptr;
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
        if (a == nullptr) return make_pair(nullptr, nullptr);
        if (a->x < value) {
            auto p = split(a->right, value);
            a->right = p.first;
            return make_pair(a, p.second);
        } else {
            auto p = split(a->left, value);
            a->left = p.second;
            return make_pair(p.first, a);
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
        if (p.second != nullptr && min(p.second)->x == new_node->x) return merge(p.first, p.second);
        else return merge(p.first, merge(new_node, p.second));
    }

    template<typename T>
    node<T>* get(node<T>* a, T value) {
        if (a == nullptr) return nullptr;
        if (a->x == value) return a;

        if (a->x < value) return search(a->right, value);
        else return search(a->left, value);
    }

    template<typename T>
    node<T>* remove(node<T>* a, T x) {
        if (a == nullptr) return nullptr;

        auto p1 = split(a, x);
        auto p2 = split(p1.second, x + 1);
        delete p2.first;
        return merge(p1.first, p2.second);
    }

}

namespace implicit_treap {

    template<typename T>
    struct node {

        node(T value, unsigned long long y) {
            this->value = value;
            this->y = y;
            size = 1;

            left = nullptr;
            right = nullptr;
        }

        void update() {
            size = (left == nullptr ? 0 : left->size) + (right == nullptr ? 0 : right->size) + 1;
        }

        T value;
        unsigned long long y;
        unsigned size;

        node* left;
        node* right;

    };

    template<typename T>
    node<T>* merge(node<T>* a, node<T>* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;

        if (a->y > b->y) {
            a->right = merge(a->right, b);
            a->update();
            return a;
        } else {
            b->left = merge(a, b->left);
            b->update();
            return b;
        }
    }

    // k-th node (in 0-indexation) is min in right tree
    template<typename T>
    pair<node<T>*, node<T>*> split(node<T>* a, unsigned k) {
        if (a == nullptr) return make_pair(nullptr, nullptr);

        unsigned l = (a->left == nullptr ? 0 : a->left->size);
        if (l < k) {
            auto p = split(a->right, k - l - 1);
            a->right = p.first;
            a->update();
            return make_pair(a, p.second);
        } else {
            auto p = split(a->left, k);
            a->left = p.second;
            a->update();
            return make_pair(p.first, a);
        }
    }

    template<typename T>
    node<T>* min(node<T>* a) {
        if (a == nullptr) return nullptr;
        if (a->left == nullptr) return a;
        return min(a->left);
    }

    template<typename T>
    node<T>* insert(node<T>* a, node<T>* new_node, unsigned pos) {
        if (a == nullptr) return new_node;
        if (new_node == nullptr) return a;

        auto p = split(a, pos);
        return merge(merge(p.first, new_node), p.second);
    }

    template<typename T>
    node<T>* get(node<T>* a, unsigned pos) {
        if (a == nullptr) return nullptr;

        auto p = split(a, pos);
        node<T>* res = min(p.second);
        a = merge(p.first, p.second);
        return res;
    }

    template<typename T>
    node<T>* remove(node<T>* a, unsigned pos) {
        if (a == nullptr) return nullptr;

        auto p1 = split(a, pos);
        auto p2 = split(p1.second, 1);
        delete p2.first;
        return merge(p1.first, p2.second);
    }

}

#endif //ALGOBASE_TREAP_H