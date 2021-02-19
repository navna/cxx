#include <cstdio>

template<typename T>
class list {
    // Узел списка
    struct node {
        // TODO
    };

    node* head;
    // node* tail;
    // size_t count;

public:

    // =======================
    // КЛАСС ИТЕРАТОРА: НАЧАЛО
    // =======================

    class iterator {
        node* n;
        iterator(node* n) : n(n) { }

        // Разрешаем классу list<T> обращаться к приватным членам итератора
        friend class list<T>;

    public:
        // TODO operator++ (prefix, postfix)
        // TODO operator-- (prefix, postfix)
        // TODO operator*
        // TODO operator==
        // TODO operator!=

        // TODO (ОПЦИОНАЛЬНО)
        // Сделать так, чтобы past-the-end указывал не на nullptr и для него была валидна операция декремента для итератора end()
    };

    // ======================
    // КЛАСС ИТЕРАТОРА: КОНЕЦ
    // ======================



    iterator insert(iterator pos, const T& value) {
        auto node = pos.n;
        // TODO
    }

    // TODO
    // Методы, которые требуются по заданию (см. в Discord'e)

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }
};

int main() {
    list<float> container;
    container.end();
}