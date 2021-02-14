#include <math.h>
#include <stdbool.h>
#include <stdio.h>

struct Point {
    float x;
    float y;

    // Конструктор по умолчанию
    Point() : x(0), y(0) {
        puts("Point: default ctor");
    }

    // Конструктор копирования
    Point(const Point& p) : x(p.x), y(p.y) {
        puts("Point: copy ctor");
    }

    // Конструктор с параметрами
    Point(const float x, const float y) : x(x), y(y) {
        puts("Point: custom ctor");
    }
};

struct Circle {
private:
    Point center;
    float radius;

public:
    // Вариант конструктора без использования списка инициализации
    //Circle(const Point& center, const float radius) {
    //    this->center = center;
    //    this->radius = radius;
    //}

    // Вариант конструктора с использованием списка инициализации
    Circle(const Point& center, const float radius) : center(center), radius(radius) { }

    Point GetCenter() {
        return center;
    }

    float GetRadius() {
        return radius;
    }

    bool IsPointInside(const Point& p) {
        const float dx = p.x - center.x;
        const float dy = p.y - center.y;
        return (dx * dx + dy * dy) < (radius * radius);
    }
};

int main() {
    Point center(1, 1);
    Circle circle(center, 4);

    puts("\nIsPointInside");
    bool isInside = circle.IsPointInside(Point(1, 4));
    printf("%d\n", isInside);
}
