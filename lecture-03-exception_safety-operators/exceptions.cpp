#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct IndexOutRange {
    const size_t index;
    const size_t size;

    IndexOutRange(const size_t index, const size_t size) : index(index), size(size) { }
};

class Vector {
    float data[16];

public:
    Vector() {
        memset(data, 0, sizeof(data));
    }

    // Самый строгий уровень: гарантия отсутствия исключений
    size_t GetSize() const noexcept {
        return sizeof(data) / sizeof(*data);
    }

    // Более слабый уровень: строгая гарантия (транзакция)
    void SetX(const size_t index, const float value) {
        const size_t size = sizeof(data) / sizeof(*data);
        if (index >= size) {
            throw IndexOutRange(index, size);
        }
        data[index] = value;
    }

    // Базовая гарантия (в случае возникновения исключения состояние данных может измениться, но всё находится в согласованном состоянии)
};

int main() {
    Vector data;

    try {
        data.SetX(30, 0);
    }
    catch (const IndexOutRange& e) {
        printf("Index %zu is out of range [0 %zu)!", e.index, e.size);
    }
}
