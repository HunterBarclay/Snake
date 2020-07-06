#include "Snake.h"
#include "engine/Debug.h"
#include "engine/core/Input.h"

Snake::Snake(int length, int startX, int startY) : Entity("Snake"),
		_defaultLength(length), _defaultX(startX), _defaultY(startY) {
	Reset();
}

Snake::~Snake() { }

void Snake::Tick() {

	if (GetLength() >= SCREEN_SIZE_SQ) {
		if (Input::GetKeyState(GLFW_KEY_ESCAPE) == 1)
			Reset();
		return;
	}

	static int SPACE;
	SPACE = Input::GetKeyState(GLFW_KEY_SPACE);

	if (SPACE == 1) {
		Paused = !Paused;
		LOG("Paused: " << Paused);
	}

	if (Paused)
		return;

	static Vector2 newDir = _direction;
	// Input stuff
	static int W, A, S, D;
	W = Input::GetKeyState(GLFW_KEY_W);
	S = Input::GetKeyState(GLFW_KEY_S);
	D = Input::GetKeyState(GLFW_KEY_D);
	A = Input::GetKeyState(GLFW_KEY_A);

	if ((W == 1 || W == 2) && _direction.Y != -1.0)
		newDir = Vector2(0.0, 1.0);
	if ((S == 1 || S == 2) && _direction.Y != 1.0)
		newDir = Vector2(0.0, -1.0);
	if ((D == 1 || D == 2) && _direction.X != -1.0)
		newDir = Vector2(1.0, 0.0);
	if ((A == 1 || A == 2) && _direction.X != 1.0)
		newDir = Vector2(-1.0, 0.0);

	static long lastTick = Utility::GetMilliseconds();
	if (Utility::GetMilliseconds() - lastTick > speed) {
		if (!Vector2::Equals(newDir + _direction, Vector2::ZERO))
			_direction = newDir;
		// LOG("Update Tick: " << (Utility::GetMilliseconds() - lastTick) << "ms");
		lastTick = Utility::GetMilliseconds();

		Vector2 projected = _body.at(0) + _direction;
		int colId = GetColBuf(projected);
		switch (colId) {
		case 0:
			_body.pop_back();
			_body.insert(_body.begin(), projected);
			SetColBuf(_body.at(_body.size() - 1), 0);
			SetColBuf(projected, 1);
			break;
		case 1:
			Died();
			return;
		case 2:
			_body.insert(_body.begin(), projected);
			SetColBuf(projected, 1);
			if (GetLength() >= SCREEN_SIZE_SQ) {
				LOG("You Won!!! Escape to restart");
				return; // Ya won
			}
			NewFruit();
			break;
		default:
			LOG("No sure how, but something went fucky wucky: " << colId);
			break;
		}

		LOG("Head => x:" << _body.at(0).X << ", y:" << _body.at(0).Y);
	}
}

void DrawBox(Vector2 pos, Window* window) {
	static double a = 2.0 / double(SCREEN_SIZE);
	static double offset = a / 2;
	static double x, y;
	x = (((pos.X + SCREEN_SIZE_HALF) + 0.5) * a) - 1.0;
	y = (((pos.Y + SCREEN_SIZE_HALF) + 0.5) * a) - 1.0;
	window->DrawSquare(Point((GLfloat)x, (GLfloat)y), a);
}

void Snake::Render(Window* window) {
	window->SetColor(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < _body.size(); i++) {
		DrawBox(_body.at(i), window);
	}
	window->SetColor(1.0f, 0.0f, 1.0f);
	if (GetLength() < SCREEN_SIZE_SQ) DrawBox(_fruitPos, window);
}

void Snake::Died() {
	std::cout << "You Died!\nScore: " << (_body.size() - 3) << std::endl;
	Reset();
}

void Snake::Reset() {
	if (_collisionBuffer == nullptr)
		_collisionBuffer = new int[SCREEN_SIZE_SQ];
	for (int i = 0; i < SCREEN_SIZE_SQ; i++)
		_collisionBuffer[i] = int(0);

	_direction = Vector2(1.0, 0.0);
	_body.clear();
	for (int i = 0; i < _defaultLength; i++) {
		_body.push_back(Vector2(_defaultX, _defaultY) - (_direction * i));
	}
	NewFruit();
	// Setup col buf
	Paused = true;
}