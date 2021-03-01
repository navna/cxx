#include <cstdio>
#include <string>

struct node {
    const int key;
    node* left;
    node* right;

    node(const int key, node* left, node* right) : key(key), left(left), right(right) { }

    node(const node&) = delete;

    node& operator=(const node&) = delete;
};

node* create_search_tree() {
    auto n1 = new node(1, nullptr, nullptr);
    auto n2 = new node(2, n1, nullptr);
    auto n3 = new node(3, n2, nullptr);
    auto n8 = new node(8, nullptr, nullptr);
    auto n9 = new node(9, n8, nullptr);
    auto n7 = new node(7, n3, n9);
    return n7;
}

void delete_tree(node* const root) {
    if (root == nullptr) {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

void print(const node* const root, const size_t level = 0) {
    static const size_t OFFSET_SIZE = 2;
    const std::string offset(level * OFFSET_SIZE, ' ');
    if (root == nullptr) {
        printf("%sNULL\n", offset.c_str());
        return;
    }
    printf("%s%d\n", offset.c_str(), root->key);
    if (root->left || root->right) {
        print(root->left, level + 1);
        print(root->right, level + 1);
    }
}

// Имеет смысл только над деревом поиска
bool recursive_search(const node* const root, const int key) {
    if (root == nullptr) {
        return false;
    }
    if (key == root->key) {
        return true;
    }
    else if (key < root->key) {
        return recursive_search(root->left, key);
    }
    else {
        return recursive_search(root->right, key);
    }
}

bool iterative_search(const node* root, const int key) {
    while (root != nullptr) {
        if (key == root->key) {
            return true;
        }
        else if (key < root->key) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return false;
}

//bool dynamic = false;
//
//void* operator new(std::size_t count) {
//    dynamic = true;
//    auto ptr = malloc(count);
//    printf("Allocated %zu bytes on address %zu.\n", count, (size_t)ptr);
//    return malloc(count);
//}
//
//void operator delete(void* ptr) {
//    printf("Deallocated on address %zu.\n", (size_t)ptr);
//    free(ptr);
//}

int main() {
    //size_t size = 1;
    //while (!dynamic) {
    //    printf("%zu\n", size);
    //    std::string s(size, 'a');
    //    ++size;
    //}

    auto root = create_search_tree();
    print(root);
    printf("\n");

    printf("RECURSIVE SEARCH\n");
    for (int key = -3; key <= 13; ++key) {
        printf("%d? %d\n", key, recursive_search(root, key));
    }
    printf("\n");

    printf("ITERATIVE SEARCH\n");
    for (int key = -3; key <= 13; ++key) {
        printf("%d? %d\n", key, iterative_search(root, key));
    }
    printf("\n");

    delete_tree(root);
}
