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

	const double speed = 50; // 50

	void SetColBuf(Vector2 pos, int v) {
		pos.X += SCREEN_SIZE_HALF;
		pos.Y += SCREEN_SIZE_HALF;

		if (pos.X < 0 || pos.X >= SCREEN_SIZE)
			return;
		if (pos.Y < 0 || pos.Y >= SCREEN_SIZE)
			return;

		SetColBuf(int((pos.Y * SCREEN_SIZE) + pos.X), v);
	}

	void SetColBuf(int index, int v) {
		if (index < 0 || index >= SCREEN_SIZE_SQ) {
			LOG("K bud, watch your fuckin bounds");
			return;
		}

		_collisionBuffer[index] = v;
	}

	int GetColBuf(Vector2 pos) {
		pos.X += SCREEN_SIZE_HALF;
		pos.Y += SCREEN_SIZE_HALF;

		if (pos.X < 0 || pos.X >= SCREEN_SIZE)
			return 1;
		if (pos.Y < 0 || pos.Y >= SCREEN_SIZE)
			return 1;

		return GetColBuf(int((pos.Y * SCREEN_SIZE) + pos.X));
	}

	int GetColBuf(int index) {
		if (index < 0 || index >= SCREEN_SIZE_SQ) {
			LOG("Checking out of view"); return 1; // They prob gon die
		}
		LOG("Index => " << index);
		return _collisionBuffer[index];
	}

	// TODO: Randomize to a location that doesn't have the body
	void NewFruit() {
		if (GetColBuf(_fruitPos) == 2) SetColBuf(_fruitPos, 0);
		static int newFruitIndex;
		newFruitIndex = Utility::Rand() % SCREEN_SIZE_SQ;
		LOG(SCREEN_SIZE_SQ);
		while (GetColBuf(newFruitIndex) == 1)
			newFruitIndex = (newFruitIndex + 1) % SCREEN_SIZE_SQ;
		SetColBuf(newFruitIndex, 2);

		LOG("Fruit Index => " << newFruitIndex);

		// Get pos from index
		_fruitPos.X = (newFruitIndex % SCREEN_SIZE) - 25;
		_fruitPos.Y = ((newFruitIndex - (newFruitIndex % SCREEN_SIZE)) / SCREEN_SIZE) - 25;

		LOG(_fruitPos.X << ", " << _fruitPos.Y);
	}

	int GetLength() { return _body.size(); }

	std::vector<Vector2>* GetBody() { return &_body; }
	Vector2* GetDirection() { return &_direction; }
	Vector2* GetFruit() { return &_fruitPos; }

	bool Paused = true;
private:
	// 1 -> player / border
	// 2 -> food
	// 0 -> nothing
	int* _collisionBuffer;
	std::vector<Vector2> _body;
	Vector2 _direction;
	Vector2 _fruitPos;

	int _defaultLength, _defaultX, _defaultY;
};