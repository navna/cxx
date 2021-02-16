#include <stdio.h>
#include <stdlib.h>
#include <utility>

class Vector {
	float* data;
	size_t size;

public:
	Vector(): data(nullptr), size(0) {
		puts("DEFAULT CTOR");
	}

	Vector(const size_t size) : data(new float[size]()), size(size) { }

	// Конструктор копирования
	Vector(const Vector& vector) : data(new float[vector.size]), size(vector.size) {
		puts("COPY CTOR");
		for (size_t i = 0; i < size; ++i) {
			data[i] = vector.data[i];
		}
	}

	// Конструктор перемещения
	Vector(Vector&& vector) noexcept : data(vector.data), size(vector.size) {
		puts("MOVE CTOR");
		vector.data = nullptr;
		//vector.size = 0;
	}

	// Оператор присваивания копированием
	Vector& operator=(const Vector& vector) {
		puts("operator=");
		Vector copy(vector); // Лучше принимать вектор по значению, тогда не нужен оператор присваивания перемещением
		Swap(copy);
		return *this;
	}

	// Оператор присваивания перемещением
	Vector& operator=(Vector&& vector) noexcept {
		puts("operator= &&");
		Swap(vector);
		return *this;
	}

	void Swap(Vector& rhs) noexcept {
		std::swap(data, rhs.data);
		std::swap(size, rhs.size);
	}

	// Деструктор
	~Vector() {
		puts("DTOR");
		delete[] data;
	}
};

Vector GetVector() {
	Vector v;
	return v;
}

int main() {
	Vector b;

	puts("Flag 1 Start");
	{
		//Vector a(std::move(b));
		//Vector a(b);
		Vector a = GetVector();
	}
	puts("Flag 1 End");
	puts("");

	puts("Flag 2 Start");
	{
		Vector a;
		a = GetVector();
	}
	puts("Flag 2 End");
}
