#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ==============================================
// ТЕМА 1: КОНСТАНТНЫЕ МЕТОДЫ, СТАТИЧЕСКИЕ МЕТОДЫ
// ==============================================

class Point {
    float x;
    float y;

public:
    // Конструктор по умолчанию
    Point() : x(0), y(0) { }

    // Конструктор с параметрами
    Point(const float x, const float y) : x(x), y(y) { }

    float GetX() const {
        return x;
    }

    float GetY() const {
        return y;
    }

    float Distance(const Point& p) const {
        puts("Non-Static Member");
        const float dx = p.x - x;
        const float dy = p.y - y;
        return sqrtf(dx * dx + dy * dy);
    }

    static float Distance(const Point& p1, const Point& p2) {
        puts("Static Member");
        return p1.Distance(p2);
    }
};

float Distance(const Point& p1, const Point& p2) {
    puts("Non Member");
    return Point::Distance(p1, p2);
}



// ==================================
// ТЕМА 2: СПОСОБЫ ПЕРЕДАЧИ ПАРАМЕТРА
// ==================================

// Передаём объект по значению (создаётся копия)
// Изменить оригинал не можем
void PrintByValue(Point point) {
    printf("%.2f %.2f\n", point.GetX(), point.GetY());
}

// Передаём указатель на объект, указатель передаётся по значению (копия самого объекта не создаётся)
// В случае отсутствия const можно изменить состояние оригинального объекта
void PrintByValuePtr(const Point* const point) {
    printf("%.2f %.2f\n", point->GetX(), point->GetY());
}

// Передаём объект по ссылке
// В случае отсутствия const можно изменить состояние оригинального объекта
void PrintByReference(const Point& point) {
    printf("%.2f %.2f\n", point.GetX(), point.GetY());
}



// =========================
// ТЕМА 3: ПРОСТРАНСТВА ИМЁН
// =========================

namespace liba {
    void f() {
        puts("liba::f");
    }
}

namespace libb {
    void f() {
        puts("libb::f");
    }
}



// ==================
// ТЕМА 4: ИСКЛЮЧЕНИЯ
// ==================

void Process() {
    int* data = (int*)calloc(10, sizeof(int));
    if (data == NULL)
        throw "Failed to allocate memory!";

    // ...

    if (true) {
        free(data);
        throw "Some condition failed!";
    }

    // ...

    free(data);
}



// =====================
// ПРИМЕРЫ ИСПОЛЬЗОВАНИЯ
// =====================

using namespace libb;

int main() {
    // ==============================================
    // ТЕМА 1: КОНСТАНТНЫЕ МЕТОДЫ, СТАТИЧЕСКИЕ МЕТОДЫ
    // ==============================================
    Point p1(1, 1);
    Point p2(2, 2);
    printf("    Distance = %.2f\n", p1.Distance(p2));         // Пример вызова метода
    printf("    Distance = %.2f\n", Point::Distance(p1, p2)); // Пример вызова статического метода
    printf("    Distance = %.2f\n", Distance(p1, p2));        // Пример вызова функции
    puts("");

    // ==================================
    // ТЕМА 2: СПОСОБЫ ПЕРЕДАЧИ ПАРАМЕТРА
    // ==================================
    Point p(1, 2);
    PrintByValue(p);     // Передача по значению самой переменной
    PrintByValuePtr(&p); // Передача по значению указателя на переменную
    PrintByReference(p); // Передача по ссылке
    puts("");

    // =========================
    // ТЕМА 3: ПРОСТРАНСТВА ИМЁН
    // =========================
    liba::f(); // Вызов функции f из пространства имён liba
    f();       // Вызов функции f из пространства имён libb
               // Можно не указывать libb:: за счёт конструкции using namespace libb перед main
    puts("");

    // ==================
    // ТЕМА 4: ИСКЛЮЧЕНИЯ
    // ==================
    try {
        puts("Flag 1");
        Process();
        puts("Flag 2");
    }
    catch (const char* message) {
        puts(message);
    }
    puts("Flag 3");
}
