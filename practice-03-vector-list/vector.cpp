#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

namespace my {

    template<typename T>
    class vector {
        T* _data;
        size_t _size;

    public:
        using iterator = T*;

        vector() : _data(nullptr), _size(0) { }

        vector(const vector<T>& rhs) : _data(new T[rhs._size]), _size(rhs._size) {
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = rhs._data[i];
            }
        }

        vector<T>& operator=(vector<T> rhs) {
            swap(rhs);
            return *this;
        }

        ~vector() {
            delete[] _data;
        }

        void swap(vector<T>& rhs) {
            std::swap(_data, rhs._data);
            std::swap(_size, rhs._size);
        }

        size_t size() const {
            return _size;
        }

        const T& operator[] (const size_t index) const {
            return _data[index];
        }

        T& operator[] (const size_t index) {
            return _data[index];
        }

        iterator insert(iterator pos, const T& item) {
            size_t index = pos - _data;
            T* newData = new T[_size + 1];
            for (size_t i = 0; i < index; ++i) {
                newData[i] = _data[i];
            }
            newData[index] = item;
            for (size_t i = index + 1; i <= _size; ++i) {
                newData[i] = _data[i - 1];
            }
            delete[] _data;
            _data = newData;
            ++_size;
            return newData + index;
        }

        iterator begin() {
            return _data;
        }

        iterator end() {
            return _data + _size;
        }
    };

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

}

int main() {
    std::vector<float> v;
    v.insert(v.begin(), 2);
    v.insert(v.begin(), 1);
    v.insert(v.end(), 3);
    
    {
        auto b = v.begin();
        auto e = v.end();
        while (b != e) {
            auto item = *b;
            printf("%.2f ", item);
            ++b;
        }
    }
    printf("\n");

    for (auto& item : v) {
        printf("%.2f ", item);
    }
    printf("\n");

    printf("%.2f", *std::min(v.begin(), v.end()));
}
