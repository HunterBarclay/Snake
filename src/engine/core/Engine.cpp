#include <thread>

#include "Engine.h"
#include "../../snek/MainScene.h"
#include "snek/Utility.h"; // TODO: Move utility into engine
#include "engine/core/Input.h"

using namespace std::chrono;

Engine::Engine(int windowWidth, int windowHeight, const char* windowName) {
	_window = new Window(windowWidth, windowHeight, windowName);
	_currentScene = new MainScene();
	// _coreThread = std::thread(MainLoop);
}

Engine::~Engine() {
	delete _window;
}

void Engine::MainLoop() {
	long lastRender = Utility::GetMilliseconds();
	_window->SetKeyCallback(Input::ProcessInput);
	while (!_halt) {
		_currentScene->Tick();
		if (Utility::GetMilliseconds() - lastRender > (1000 / 60)) {

			std::cout << "Render Tick: " << (Utility::GetMilliseconds() - lastRender) << "ms" << std::endl;

			lastRender = Utility::GetMilliseconds();

			_window->BeginDraw();
			_currentScene->Render();
			// _window->DrawSquare(Point(0.0, 0.0), 0.5);
			_window->Render();
		}

		_halt = _window->WindowClosed();
	}
}