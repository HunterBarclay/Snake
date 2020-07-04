#pragma once

#include <GLFW/glfw3.h>

class Input {
public:
	static void ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
		static int* keyStates = new int[256];
		keyStates[key] = action;
		Instance()->KeyStates = keyStates;
	}

	static int GetKeyState(int key) {
		if (key > 255 || key < 0)
			throw 20;
		if (Instance()->KeyStates == nullptr)
			return -1;
		return Instance()->KeyStates[key];
	}

	int* KeyStates = nullptr;
private:
	Input() { }
	~Input() { }

	static Input* Instance() {
		static Input instance;
		return &instance;
	}
};