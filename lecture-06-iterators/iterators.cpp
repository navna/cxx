#include <stdio.h>
#include <string.h>

template<typename Iterator>
Iterator min(Iterator begin, Iterator end) {
    Iterator found = begin;
    while (begin != end) {
        if (*begin < *found) {
            found = begin;
        }
        ++begin;
    }
    return found;
}

struct node {
    float data;
    node* next;

    node(const float data, node* const next) : data(data), next(next) { }
};

node* list_add(node* const head, const float value) {
    auto ptr = new node(value, NULL);
    if (head == NULL) {
        return ptr;
    }
    auto tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = ptr;
    return head;
}

class list_iterator {
    node* n;

public:
    list_iterator(node* n) : n(n) { }

    // Префиксный инкремент. Семантический смысл: переход к следующему элементу в список
    list_iterator& operator++() {
        n = n->next;
        return *this;
    }

    // Постфиксный инкремент. Семантический смысл: переход к следующему элементу в спискк
    list_iterator operator++(int) {
        auto copy = *this;
        n = n->next;
        return copy;
    }

    float operator*() const {
        return n->data;
    }

    bool operator!=(list_iterator rhs) {
        return n != rhs.n;
    }
};

int main() {
    // МАССИВ (в качестве итератора выступает указатель)
    float data[] = { 5, 1, 9, 2 };
    printf("%f\n", *min(data, data + 4));

    // СПИСОК (в качестве итератора выступает list_iterator)
    node* head = NULL;
    head = list_add(head, 5);
    head = list_add(head, 1);
    head = list_add(head, 9);
    head = list_add(head, 2);
    {
        list_iterator begin(head);
        list_iterator end(NULL);
        printf("%f\n", *min(begin, end));
    }
}
