#ifndef SNAKE_UTILITY
#define SNAKE_UTILITY

#include <iostream>
#include <ctime>
#include <cmath>
#include <chrono>
#include <stdlib.h>

#include "engine/Debug.h"

using namespace std::chrono;

#define SCREEN_SIZE 50
#if SCREEN_SIZE % 2 == 1
#pragma message("Screen size ain't even steven. This might make things go fucky wucky")
#endif
#define SCREEN_SIZE_SQ int(std::pow(SCREEN_SIZE, 2))
#define SCREEN_SIZE_HALF SCREEN_SIZE / 2

namespace {
	class Utility {
	public:
		static long GetMilliseconds() {
			return (long)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		}

		static int Rand() {
			return rand() + GetMilliseconds();
		}
	};

	struct Vector2 {
	public:
		Vector2() : X(0.0), Y(0.0) { }
		Vector2(double x, double y) : X(x), Y(y) { }
		double X, Y;

		static bool Equals(Vector2 a, Vector2 b) { // AHHHHHHHHHHHH fuck c++
			return (a.X == b.X && a.Y == b.Y);
		}

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

		static Vector2 ZERO, UP, DOWN, LEFT, RIGHT; // I could give less of shit if these were accidently modified
		// because the effect I want it to much to type at this level of shits given
	};
}

Vector2 Vector2::ZERO = Vector2(0, 0);
Vector2 Vector2::UP = Vector2(0, 1);
Vector2 Vector2::DOWN = Vector2(0, -1);
Vector2 Vector2::RIGHT = Vector2(1, 0);
Vector2 Vector2::LEFT = Vector2(-1, 0);

#endif