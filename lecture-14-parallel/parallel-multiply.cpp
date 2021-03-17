#include <chrono>

#include "matrix.h"
#include "multiply.h"
#include "multiply-parallel-v1.h"

using namespace std;
using namespace std::chrono;

int main() {
    const size_t n = 1024;
    matrix<size_t> a(n, n);
    matrix<size_t> b(n, n);
    matrix<size_t> rr(n, n);
    matrix<size_t> r1(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            a(i, j) = i + j;
            b(i, j) = i * j;
        }
    }

    const auto seq1_begin = steady_clock::now();
    multiply(rr, a, b);
    const auto seq2_end = steady_clock::now();

    const auto par1_begin = steady_clock::now();
    multiply_v1(r1, a, b);
    const auto par2_end = steady_clock::now();

    cout << " SEQ: " << duration_cast<milliseconds>(seq2_end - seq1_begin).count() << endl;
    cout << "PAR1: " << duration_cast<milliseconds>(par2_end - par1_begin).count() << endl;
    cout << "VALIDATION: " << (rr == r1) << endl;
}
