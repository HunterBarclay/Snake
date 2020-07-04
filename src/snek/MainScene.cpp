#include "MainScene.h"

#include <iostream>

#include "engine/core/Input.h"

MainScene::MainScene() : Scene("MainScene"), _player(3, 5, 5) { }

MainScene::~MainScene() { }

void MainScene::Tick() {

	auto dir = _player.GetDirection();
	// Input stuff
	if (Input::GetKeyState(GLFW_KEY_W) == GLFW_PRESS)
		(*dir) = Vector2(0.0, 1.0);
	if (Input::GetKeyState(GLFW_KEY_S) == GLFW_PRESS)
		(*dir) = Vector2(0.0, -1.0);
	if (Input::GetKeyState(GLFW_KEY_D) == GLFW_PRESS)
		(*dir) = Vector2(1.0, 0.0);
	if (Input::GetKeyState(GLFW_KEY_A) == GLFW_PRESS)
		(*dir) = Vector2(-1.0, 0.0);

	static long lastTick = Utility::GetMilliseconds();
	if (Utility::GetMilliseconds() - lastTick > _player.speed) {

		std::cout << "Update Tick: " << (Utility::GetMilliseconds() - lastTick) << "ms" << std::endl;

		lastTick = Utility::GetMilliseconds();

		auto body = _player.GetBody();
		static bool eaten = false;

		Vector2 projected = body->at(0) + *dir;
		switch (_player.GetColBuf(projected)) {
		case 1:
			//die
			break;
		case 2:
			eaten = true;
			break;
		}

		// Clear player from col buf
		for (int i = 0; i < body->size(); i++) {
			_player.SetColBuf(body->at(i), 0);
		}

		auto dir = _player.GetDirection();
		if (!eaten) {
			body->pop_back();
		}
		body->insert(body->begin(), projected);

		// Update col buf
		for (int i = 0; i < body->size(); i++) {
			if (_player.GetColBuf(body->at(i)) == 0) _player.SetColBuf(body->at(i), 1);
		}

		if (eaten) {
			_player.NewFruit();
			eaten = false;
		}
	}
}

void DrawBox(Vector2 pos) {
	static double a = 2.0 / 50.0;
	static double offset = a / 2;
	static double x, y;
	x = (((pos.X + 25) * a) + offset) - 1.0;
	y = (((pos.Y + 25) * a) - offset) - 1.0;
	// std::cout << "X:" << x << std::endl << "Y:" << y << std::endl;
	Engine::GetInstance()->GetWindow()->DrawSquare(Point((GLfloat)x, (GLfloat)y), a);
}

void MainScene::Render() {
	std::vector<Vector2>* body = _player.GetBody();
	Engine::GetInstance()->GetWindow()->SetColor(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < body->size(); i++) {
		DrawBox(body->at(i));
	}
	Engine::GetInstance()->GetWindow()->SetColor(1.0f, 0.0f, 1.0f);
	DrawBox(*_player.GetFruit());
}