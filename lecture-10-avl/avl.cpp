#include <algorithm>
#include <cstdio>
#include <string>

template<typename TKey, typename TCompare = std::less<TKey>>
class set {
    struct node {
        const TKey key;
        uint8_t height;
        node* left;
        node* right;

        node(const int key) : key(key), height(1), left(nullptr), right(nullptr) { }

        node(const node&) = delete;

        node& operator=(const node&) = delete;
    };

    node* _root;
    size_t _size;

    static void clear(node* const root) {
        if (root == nullptr) {
            return;
        }
        clear(root->left);
        clear(root->right);
        delete root;
    }

    static void debug(const node* const root, const size_t level = 0) {
        static const size_t OFFSET_SIZE = 2;
        const std::string offset(level * OFFSET_SIZE, ' ');
        if (root == nullptr) {
            printf("%sNULL\n", offset.c_str());
            return;
        }
        printf("%s%d\n", offset.c_str(), root->key);
        if (root->left || root->right) {
            debug(root->left, level + 1);
            debug(root->right, level + 1);
        }
    }

    static uint8_t height(node* p) {
        if (p == nullptr) {
            return 0;
        }
        return p->height;
    }

    static void update_height(node* const p) {
        p->height = std::max(height(p->left), height(p->right)) + 1;
    }

    static node* rotate_right(node* const p) {
        auto q = p->left;
        p->left = q->right;
        q->right = p;
        update_height(p);
        update_height(q);
        return q;
    }

    static node* rotate_left(node* const q) {
        auto p = q->right;
        q->right = p->left;
        p->left = q;
        update_height(q);
        update_height(p);
        return p;
    }

    static node* balance(node* p) {
        update_height(p);
        auto dh = height(p->left) - height(p->right);
        if (dh == 2) {
            // if h(s) > h(A)
            if (height(p->left->right) > height(p->left->left)) {
                p->left = rotate_left(p->left);
            }
            p = rotate_right(p);
        }
        else if (dh == -2) {
            // !!!
            if (height(p->right->left) > height(p->right->right)) {
                p->right = rotate_right(p->right);
            }
            p = rotate_left(p);
        }
        return p;
    }

    static node* insert(node* p, const TKey& key) {
        if (p == nullptr) {
            return new node(key);
        }
        TCompare less;
        if (less(key, p->key)) {
            p->left = insert(p->left, key);
        }
        else if (less(p->key, key)) {
            p->right = insert(p->right, key);
        }
        return balance(p);
    }

public:
    set() : _root(nullptr), _size(0) { }

    set(const set<TKey, TCompare>&) = delete;

    set<TKey, TCompare>& operator=(const set<TKey, TCompare>&) = delete;

    size_t size() const {
        return _size;
    }

    // TODO return iterator
    void insert(const TKey& key) {
        _root = insert(_root, key);
    }

    void clear() {
        clear(_root);
        _root = nullptr;
    }

    void debug() {
        debug(_root);
    }

    ~set() {
        clear();
    }
};

//// Имеет смысл только над деревом поиска
//bool recursive_search(const node* const root, const int key) {
//    if (root == nullptr) {
//        return false;
//    }
//    if (key == root->key) {
//        return true;
//    }
//    else if (key < root->key) {
//        return recursive_search(root->left, key);
//    }
//    else {
//        return recursive_search(root->right, key);
//    }
//}

int main() {
    set<int> s;

    for (int i = 1; i <= 12; ++i) {
        s.insert(i);
    }
    
    s.debug();
    printf("\n");
}
