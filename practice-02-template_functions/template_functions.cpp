#include <stdio.h>
#include <math.h>

struct complex {
    float x;
    float y;

    complex(const float x, const float y) : x(x), y(y) { }

    float abs() const {
        return sqrtf(x * x + y * y);
    }

    bool operator<(const complex& rhs) const {
        return abs() < rhs.abs();
    }
};

template<typename T>
ptrdiff_t min(const T* const data, const size_t n) {
    if (n == 0) {
        return -1;
    }
    size_t index = 0;
    for (size_t i = 1; i < n; ++i) {
        if (data[i] < data[index]) {
            index = i;
        }
    }
    return index;
}

int main() {
    int intData[] = { 4, 3, 1, 2 };
    complex complexData[] = { {4, 3}, {1, 3}, {3, 3} };

    printf("%td\n", min(intData, sizeof(intData) / sizeof(*intData)));
    printf("%td\n", min(complexData, sizeof(complexData) / sizeof(*complexData)));
}
