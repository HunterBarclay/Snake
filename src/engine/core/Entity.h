#pragma once

#include <string>

#include "Window.h"

class Entity {
public:
	Entity(std::string name) : _name(name) { }
	~Entity() { }

	virtual void Tick() = 0;
	virtual void Render(Window* window) = 0;

	std::string GetName() { return _name; }
protected:
	std::string _name;
};