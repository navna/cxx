#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct A {
    int x;
    int y;

    // Конструктор по умолчанию
    A() : x(0), y(0) { }

    // Конструктор копирования
    A(const A& rhs) : x(rhs.x), y(rhs.y) { }

    //// Запрещённый конструктор копирования
    //A(const A& rhs) = delete;

    //// Присвоение копированием
    //A& operator=(const A& rhs) {
    //    x = rhs.x;
    //    y = rhs.y;
    //    return *this;
    //}
    
    //// Запрещённый оператор присваивания
    //A& operator=(const A& rhs) = delete;
};

int main() {
    A a1, a2;  // Конструктор по умолчанию
    A a3(a1);  // Конструктор копирования
    A a4 = a1; // Конструктор копирования
    a1 = a2;   // Оператор присваивания копированием
}
