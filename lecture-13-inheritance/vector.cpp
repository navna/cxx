#include <cstdio>
#include <vector>

struct vector {
    virtual size_t size() const = 0;

    virtual float get(size_t index) const = 0;

    virtual void set(size_t index, float value) = 0;

    virtual ~vector() = default;
};

class memory_vector : public vector {
    std::vector<float> _data;

public:
    memory_vector(const size_t size) : _data(size) { }

    size_t size() const override {
        return _data.size();
    }

    float get(const size_t index) const override {
        return _data[index];
    }

    void set(const size_t index, const float value) override {
        _data[index] = value;
    }
};

class slice_vector : public vector {
    vector& _v;
    size_t _offset;
    size_t _size;

public:
    slice_vector(vector& v, const size_t offset, const size_t size) : _v(v), _offset(offset), _size(size) { }

    size_t size() const override {
        return _size;
    }

    float get(const size_t index) const override {
        return _v.get(_offset + index);
    }

    void set(const size_t index, const float value) override {
        _v.set(_offset + index, value);
    }
};

void print(const vector& v) {
    const auto n = v.size();
    for (size_t i = 0; i < n; ++i) {
        printf("%.2f ", v.get(i));
    }
    printf("\n");
}

int main() {
    memory_vector v(8);
    for (size_t i = 0; i < v.size(); ++i)
        v.set(i, (float)i);

    slice_vector sv1(v, 2, 4);
    slice_vector sv2(sv1, 1, 2);

    print(v);
    print(sv1);
    print(sv2);
    printf("\n");

    sv2.set(0, -1);

    print(v);
    print(sv1);
    print(sv2);
}
