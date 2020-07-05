#pragma once

#include <vector>
#include <stdlib.h>

#include "Utility.h"

class Snake {
public:
	Snake(int length, int startX, int startY);
	~Snake();

	void Reset(int length, int startX, int startY);

	const double speed = 50;

	void SetColBuf(Vector2 pos, int v) {
		pos.X += 25;
		pos.Y += 25;
		if (pos.X < 0 || pos.X > 50)
			return;
		if (pos.Y < 0 || pos.Y > 50)
			return;
		_collisionBuffer[int((pos.Y * 50) + pos.X)] = v;
	}

	int GetColBuf(Vector2 pos) {
		pos.X += 25;
		pos.Y += 25;
		if (pos.X < 0 || pos.X > 50)
			return 1;
		if (pos.Y < 0 || pos.Y > 50)
			return 1;
		return _collisionBuffer[int((pos.Y * 50) + pos.X)];
	}

	void NewFruit(bool first = false) {
		if (!first) SetColBuf(_fruitPos, 0);
		_fruitPos = Vector2((rand() % 50) - 25, (rand() % 50) - 25); // TODO: Randomize
		SetColBuf(_fruitPos, 2);
	}

	std::vector<Vector2>* GetBody() { return &_body; }
	Vector2* GetDirection() { return &_direction; }
	Vector2* GetFruit() { return &_fruitPos; }

	bool Paused = true;
private:
	// 1 -> player / border
	// 2 -> food
	// 0 -> nothing
	int* _collisionBuffer;
	int _length;
	std::vector<Vector2> _body;
	Vector2 _direction;
	Vector2 _fruitPos;
};