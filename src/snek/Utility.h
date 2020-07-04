#pragma once

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std::chrono;

class Utility {
public:
	static long GetMilliseconds() {
		return (long)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}
};

struct Vector2 {
public:
	Vector2() : X(0.0), Y(0.0) { }
	Vector2(double x, double y) : X(x), Y(y) { }
	double X, Y;

	Vector2 Add(Vector2 a) {
		return Vector2(X + a.X, Y + a.Y);
	}

	Vector2 Subtract(Vector2 a) {
		return Vector2(X - a.X, Y - a.Y);
	}

	Vector2 Multiply(double a) {
		return Vector2(X * a, Y * a);
	}

	Vector2 operator+(Vector2 a) {
		return Add(a);
	}
	Vector2 operator-(Vector2 a) {
		return Subtract(a);
	}
	Vector2 operator*(double a) {
		return Multiply(a);
	}
};