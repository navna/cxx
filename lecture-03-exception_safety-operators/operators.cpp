#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Complex {
    const float re;
    const float im;

    Complex(const float re, const float im) : re(re), im(im) { }

    Complex Sum(const Complex c) const {
        return Complex(re + c.re, im + c.im);
    }

    Complex operator+(const Complex rhs) const {
        return Complex(re + rhs.re, im + rhs.im);
    }

    Complex operator*(const float rhs) const {
        return Complex(re * rhs, im * rhs);
    }
};

void Print(const Complex c) {
    printf("%.2f %.2f\n", c.re, c.im);
}

int main() {
    Complex c1(1, 2);
    Complex c2(5, 3);
    Complex c3(-1, -2);
    Complex c4(4, 3);
    Complex c5(-5, -3);
    auto r1 = c1.Sum(c2).Sum(c3).Sum(c4).Sum(c5);
    auto r2 = c1 + c2 + c3 + c4 + c5;
    auto r3 = c1 * 3;
    // auto r4 = 4 * c1;
    Print(r1);
    Print(r2);
}
