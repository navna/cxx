#include <cstdio>

struct A {
    void f() const {
        puts("A::f()");
    }

    virtual void vf() const {
        puts("A::vf()");
    }

    ~A() {
        puts("~A()");
    }
};

struct B: public A {
    void f() const {
        puts("B::f()");
    }

    void vf() const override {
        puts("B::vf()");
    }

    ~B() {
        puts("~B()");
    }
};

int main() {
    printf("%zu %zu\n", sizeof(A), sizeof(B));

    A* paa = new A;   //   Формальный тип: A   Фактический тип: A
    A* pab = new B;   //   Формальный тип: A   Фактический тип: B
    B* pbb = new B;   //   Формальный тип: B   Фактический тип: B

    paa->f(); // A
    pab->f(); // A
    pbb->f(); // B
    printf("\n");

    paa->vf(); // A
    pab->vf(); // B
    pbb->vf(); // B

    delete paa; // ~A
    delete pab; //  ! ~A
    delete pbb; // ~B ~A
}
