#pragma once

#include "GLFW/glfw3.h"
#include <iostream>

struct Point {
public:
	Point() : X(0.0f), Y(0.0f) { }
	Point(double x, double y) : X((GLfloat)x), Y((GLfloat)y) {
		if (X > 1.0) X = 1.0;
		if (X < -1.0) X = -1.0;
		if (Y > 1.0) Y = 1.0;
		if (Y < -1.0) Y = -1.0;
	}

	GLfloat X, Y;
};

class Window {
public:
	Window(int width, int height, const char* name);
	~Window();

	void BeginDraw();
	void SetColor(GLfloat r, GLfloat g, GLfloat b);
	void DrawTriangle(Point a, Point b, Point c);
	void DrawSquare(Point position, double sideLength);
	void Render();

	int GetWidth() { return _width; }
	int GetHeight() { return _height; }

	bool WindowClosed() { return glfwWindowShouldClose(_window); }

	void SetKeyCallback(GLFWkeyfun callback);
private:
	void InitWindow();

	GLFWwindow* _window;
	int _width, _height;
	const char* _name;
};