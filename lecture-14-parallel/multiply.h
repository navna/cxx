#pragma once

#include <stdexcept>

#include "matrix.h"

template<typename T>
void multiply(matrix<T>& result, const matrix<T>& lhs, const matrix<T>& rhs) {
    const auto rows1 = lhs.rows();
    const auto cols1 = lhs.cols();
    const auto rows2 = rhs.rows();
    const auto cols2 = rhs.cols();
    const auto rows = result.rows();
    const auto cols = result.cols();

    if (rows2 != cols1 || rows1 != rows || cols2 != cols) {
        throw std::runtime_error("Invalid matrix size!");
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            auto value = T();
            for (size_t k = 0; k < rows2; ++k) {
                value += lhs(i, k) * rhs(k, j);
            }
            result(i, j) = value;
        }
    }
}
