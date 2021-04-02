#pragma once

#include <functional>
#include <mutex>
#include <stdexcept>
#include <thread>

#include <iostream>

#include "matrix.h"

template<typename T>
class matrix_multiplier_v3 {
    matrix<T>& _result;
    const matrix<T>& _lhs;
    const matrix<T>& _rhs;
    std::mutex _mutex;
    size_t _next_i;
    size_t _next_j;

    void multiply_thread() {
        const auto rows = _result.rows();
        const auto cols = _result.cols();
        const auto n = _rhs.rows(); // == _lhs.cols()

        while (true) {
            size_t i;
            size_t j;

            // Критическая секция
            {
                std::lock_guard<std::mutex> lk(_mutex);
                i = _next_i;
                j = _next_j;
                if (i == rows) {
                    return;
                }
                if (_next_j == cols - 1) {
                    ++_next_i;
                    _next_j = 0;
                }
                else {
                    ++_next_j;
                }
            }

            auto value = T();
            for (size_t k = 0; k < n; ++k) {
                value += _lhs(i, k) * _rhs(k, j);
            }
            _result(i, j) = value;
        }
    }

public:
    matrix_multiplier_v3(matrix<T>& result, const matrix<T>& lhs, const matrix<T>& rhs) : _result(result), _lhs(lhs), _rhs(rhs), _next_i(0), _next_j(0) {
        const auto rows1 = lhs.rows();
        const auto cols1 = lhs.cols();
        const auto rows2 = rhs.rows();
        const auto cols2 = rhs.cols();
        const auto rows = result.rows();
        const auto cols = result.cols();

        if (rows2 != cols1 || rows1 != rows || cols2 != cols) {
            throw std::runtime_error("Invalid matrix size!");
        }
    }

    // Сам метод умножения не является потокобезопасным!
    void multiply(size_t thread_count = 0) {
        if (thread_count == 0) {
            thread_count = std::thread::hardware_concurrency();
            if (thread_count == 0) {
                thread_count = 1;
            }
        }

        std::vector<std::thread> threads;
        for (size_t i = 0; i < thread_count; ++i) {
            threads.emplace_back(&matrix_multiplier_v3<T>::multiply_thread, this);
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }
};
