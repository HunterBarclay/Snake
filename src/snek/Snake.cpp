#include "Snake.h"
#include "engine/Debug.h"

Snake::Snake(int length, int startX, int startY) {
	Reset(length, startX, startY);
}

Snake::~Snake() {

}

void Snake::Reset(int length, int startX, int startY) {
	if (_collisionBuffer != nullptr) {
		// delete _collisionBuffer;
		for (int i = 0; i < 50 * 50; i++)
			_collisionBuffer[i] = 0;
	}
	else {
		_collisionBuffer = new int[50 * 50];
	}
	_length = length;
	_direction = Vector2(1.0, 0.0);
	_body.clear();
	for (int i = 0; i < length; i++) {
		_body.push_back(Vector2(startX, startY) - (_direction * i));
	}
	static bool first = true;
	NewFruit(first);
	if (first) first = false;
	// Setup col buf
	Paused = true;
}