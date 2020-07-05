#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#include "engine/Debug.h"

/*
None = 0
Pressed = 1
Held = 2
Released = 3
*/

class Input {
public:
	static void ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
		// LOG("Key: " << key << std::endl << "Action: " << action);
		static int* keyStates = Instance()->KeyStates;
		if (action > 0) {
			if (keyStates[key] == 0)
				keyStates[key] = 1;
			else if (keyStates[key] == 1)
				keyStates[key] = 2;
		}
		else {
			keyStates[key] = 3;
		}
	}

	static int GetKeyState(int key) {
		if (key > 255 || key < 0)
			throw 20;
		if (Instance()->KeyStates == nullptr)
			return -1;

		static int keyState;
		keyState = Instance()->KeyStates[key];
		Instance()->KeyStates[key] = 0;
		return keyState;
	}

	int* KeyStates;
private:
	Input() { KeyStates = new int[256]; }
	~Input() { }

	static Input* Instance() {
		static Input instance;
		return &instance;
	}
};