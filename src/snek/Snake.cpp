#include "Snake.h"

Snake::Snake(int length, int startX, int startY) {
	Reset(length, startX, startY);
}

Snake::~Snake() {

}

void Snake::Reset(int length, int startX, int startY) {
	if (_collisionBuffer != nullptr)
		delete _collisionBuffer;
	_collisionBuffer = new int[50 * 50];
	_length = length;
	_direction = Vector2(0.0, -1.0);
	auto d = Vector2(1.0, 0.0);
	for (int i = 0; i < length; i++) {
		_body.push_back(Vector2(startX, startY) - (d * i));
	}
	static bool first = true;
	NewFruit(first);
	if (first) first = false;
	// Setup col buf
}