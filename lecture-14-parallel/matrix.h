#pragma once

#include <iostream>
#include <vector>

template<typename T>
class matrix final {
    std::vector<T> _data;
    size_t _rows;
    size_t _cols;

public:
    matrix(const size_t rows, const size_t cols) : _data(rows * cols), _rows(rows), _cols(cols) { }

    T& operator()(const size_t i, const size_t j) {
        return _data[i * _cols + j];
    }

    const T& operator()(const size_t i, const size_t j) const {
        return _data[i * _cols + j];
    }

    size_t rows() const {
        return _rows;
    }

    size_t cols() const {
        return _cols;
    }

    bool operator==(const matrix<T>& rhs) const {
        return _data == rhs._data;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& m) {
    const auto rows = m.rows();
    const auto cols = m.cols();

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (j > 0) {
                os << ' ';
            }
            os << m(i, j);
        }
        os << std::endl;
    }

    return os;
}
