#include "Window.h"

using namespace std;

Window::Window(int width, int height, const char* name) : _width(width), _height(height), _name(name) {
    InitWindow();
}

Window::~Window() {
    glfwTerminate();
    delete _name;
    delete _window;
}

void Window::InitWindow() {
    /* Initialize the library */
    if (!glfwInit())
        cout << "O dear" << endl;

    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(_width, _height, _name, NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        cout << "O no" << endl;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    GLFWwindow* wind = _window;
}

void Window::BeginDraw() {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SetColor(GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
}

void Window::Render() {
    /* Swap front and back buffers */
    glfwSwapBuffers(_window);

    /* Poll for and process events */
    glfwPollEvents();
}

void Window::DrawTriangle(Point a, Point b, Point c) {

    // glColor3b(255, 0, 0);

    glBegin(GL_TRIANGLES);

    glVertex2f(a.X, a.Y);
    glVertex2f(b.X, b.Y);
    glVertex2f(c.X, c.Y);

    glEnd();
}

void Window::DrawSquare(Point pos, double sideLength) {
    glBegin(GL_POLYGON);
    float a = sideLength / 2;
    glVertex2f(pos.X - a, pos.Y - a);
    glVertex2f(pos.X - a, pos.Y + a);
    glVertex2f(pos.X + a, pos.Y + a);
    glVertex2f(pos.X + a, pos.Y - a);
    glEnd();
}

void Window::SetKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(_window, callback);
}