#include <stdio.h>
#include <stdlib.h>
#include <utility>

class Vector {
	float* data;
	size_t size;

public:
	Vector(const size_t size) : data(new float[size]()), size(size) { }

	Vector(const Vector& vector) : data(new float[vector.size]), size(vector.size) {
		// memcpy
		puts("ctor");
		for (size_t i = 0; i < size; ++i) {
			data[i] = vector.data[i];
		}
	}

	Vector& operator=(const Vector& vector) {
		Vector copy(vector);
		Swap(copy);
		return *this;
	}

	void Swap(Vector& vector) noexcept {
		std::swap(data, vector.data);
		std::swap(size, vector.size);
	}

	size_t GetSize() const {
		return size;
	}

	float operator[](const size_t index) const {
		return data[index];
	}

	float& operator[](const size_t index) {
		return data[index];
	}

	//float Get(size_t index) const {
	//	return data[index];
	//}

	//void Set(size_t index, float value) {
	//	data[index] = value;
	//}

	~Vector() {
		delete[] data;
	}
};

void Print(const Vector& v) {
	for (size_t i = 0; i < v.GetSize(); ++i) {
		printf("%.2f ", v[i]);
	}
	printf("\n");
}

int main() {
	Vector v1(1);
	v1[0] = 1;
	Vector v2(1);
	v2[0] = 2;

	Print(v1);
	Print(v2);

	//std::swap(v1, v2);
	v1.Swap(v2);
	//v2.Swap(v1);

	Print(v1);
	Print(v2);
}
