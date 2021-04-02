#include <cstddef>
#include <cstdio>
#include <cstring>

struct person {
    char name[16];
    float height;
    float weight;

    person(const char* name, const float height, const float weight) : height(height), weight(weight) {
        strcpy(this->name, name);
    }
};

bool person_height_comparator_f(const person& lhs, const person& rhs) {
    return lhs.height < rhs.height;
}

bool person_weight_comparator_f(const person& lhs, const person& rhs) {
    return lhs.weight < rhs.weight;
}

struct person_height_comparator {
    bool operator()(const person& lhs, const person& rhs) {
        return lhs.height < rhs.height;
    }
};

struct person_weight_comparator {
    bool operator()(const person& lhs, const person& rhs) {
        return lhs.weight < rhs.weight;
    }
};

template<typename T, typename Comparator>
ptrdiff_t min(const T* const data, const size_t n, Comparator comparator) {
    if (n == 0) {
        return -1;
    }
    size_t index = 0;
    for (size_t i = 1; i < n; ++i) {
        if (comparator(data[i], data[index])) {
            index = i;
        }
    }
    return index;
}

int main() {
    person data[] = { {"Andrey", 178, 75}, {"Vladimir", 210, 80}, {"Maria", 180, 60} };

    printf("%td\n", min(data, sizeof(data) / sizeof(*data), person_height_comparator_f));
    printf("%td\n", min(data, sizeof(data) / sizeof(*data), person_weight_comparator_f));

    person_height_comparator height_comparator;
    person_weight_comparator weight_comparator;

    // ptrdiff_t min(const person* const data, const size_t n, person_height_comparator comparator)
    printf("%td\n", min(data, sizeof(data) / sizeof(*data), height_comparator));

    // ptrdiff_t min(const person* const data, const size_t n, person_weight_comparator comparator)
    printf("%td\n", min(data, sizeof(data) / sizeof(*data), weight_comparator));
}
