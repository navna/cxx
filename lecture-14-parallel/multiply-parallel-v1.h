#pragma once

#include <functional>
#include <stdexcept>
#include <thread>

#include "matrix.h"

template<typename T>
void multiply_v1_thread(matrix<T>& result, const matrix<T>& lhs, const matrix<T>& rhs, const size_t row_begin, const size_t row_end) {
    const auto rows2 = rhs.rows();
    const auto cols = result.cols();

    for (size_t i = row_begin; i < row_end; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            auto value = T();
            for (size_t k = 0; k < rows2; ++k) {
                value += lhs(i, k) * rhs(k, j);
            }
            result(i, j) = value;
        }
    }
}

template<typename T>
void multiply_v1(matrix<T>& result, const matrix<T>& lhs, const matrix<T>& rhs, size_t thread_count = 0) {
    if (thread_count == 0) {
        thread_count = std::thread::hardware_concurrency();
        if (thread_count == 0) {
            thread_count = 1;
        }
    }

    const auto rows1 = lhs.rows();
    const auto cols1 = lhs.cols();
    const auto rows2 = rhs.rows();
    const auto cols2 = rhs.cols();
    const auto rows = result.rows();
    const auto cols = result.cols();

    if (rows2 != cols1 || rows1 != rows || cols2 != cols) {
        throw std::runtime_error("Invalid matrix size!");
    }

    if (rows % thread_count != 0) {
        throw std::runtime_error("Invalid thread count!");
    }

    const auto rows_per_thread = rows / thread_count;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < thread_count; ++i) {
        threads.emplace_back(multiply_v1_thread<T>, std::ref(result), std::cref(lhs), std::cref(rhs), i * rows_per_thread, (i + 1) * rows_per_thread);
    }

    for (auto& thread: threads) {
        thread.join();
    }
}
