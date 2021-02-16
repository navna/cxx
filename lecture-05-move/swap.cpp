#include <stdio.h>
#include <utility>

struct A {
    A() = default;

    A(const A&) {
        puts("COPY CTOR");
    }

    A(A&&) noexcept {
        puts("MOVE CTOR");
    }

    A& operator=(const A&) {
        puts("COPY ASSIGN");
        return *this;
    }

    A& operator=(A&&) noexcept {
        puts("MOVE ASSIGN");
        return *this;
    }

    void swap(A&) {
        puts("MEMBER SWAP");
    }
};

void swap(A& lhs, A& rhs) {
    puts("NON-MEMBER SWAP");
    lhs.swap(rhs);
}

using namespace std;

template<typename T>
void Swap(T& lhs, T& rhs) {
    auto t = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(t);
}

int main() {
    A a1, a2;

    Swap(a1, a2);

    swap(a1, a2);
}
