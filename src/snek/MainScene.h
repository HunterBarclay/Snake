#pragma once

#include "Snake.h"
#include "../engine/core/Engine.h"
#include "../engine/core/Scene.h"

class MainScene: public Scene {
public:
	MainScene();
	~MainScene();

	void Tick();
	void Render();
private:
	Snake _player;
};