#pragma once

#include <vector>
#include <stdlib.h>

#include "Utility.h"
#include "engine/core/Entity.h"
#include "engine/Debug.h"

class Snake: public Entity {
public:
	Snake(int length, int startX, int startY);
	~Snake();

	void Tick();
	void Render(Window* window);

	void Died();
	void Reset();

	const double speed = 50;

	void SetColBuf(Vector2 pos, int v) {
		pos.X += SCREEN_SIZE_HALF;
		pos.Y += SCREEN_SIZE_HALF;

		// Bounds Detection
		if (pos.X < 0 || pos.X >= SCREEN_SIZE)
			return;
		if (pos.Y < 0 || pos.Y >= SCREEN_SIZE)
			return;

		_collisionBuffer[int((pos.Y * SCREEN_SIZE) + pos.X)] = v;
	}

	int GetColBuf(Vector2 pos) {
		pos.X += SCREEN_SIZE_HALF;
		pos.Y += SCREEN_SIZE_HALF;

		// Bounds detection
		if (pos.X < 0 || pos.X >= SCREEN_SIZE)
			return 1;
		if (pos.Y < 0 || pos.Y >= SCREEN_SIZE)
			return 1;

		int index = int((pos.Y * SCREEN_SIZE) + pos.X);
		int a = _collisionBuffer[index];

		if (a != 0 && a != 1 && a != 2) {
			LOG("Index => " << index);
		}

		return a;
	}

	// TODO: Randomize to a location that doesn't have the body
	void NewFruit(bool first = false) {
		if (!first) SetColBuf(_fruitPos, 0);
		_fruitPos = Vector2((rand() % (SCREEN_SIZE - 1)) - SCREEN_SIZE_HALF, 
			(rand() % (SCREEN_SIZE - 1)) - SCREEN_SIZE_HALF);
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

	int _defaultLength, _defaultX, _defaultY;
};