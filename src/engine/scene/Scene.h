#pragma once

class Scene {
public:
	Scene(const char* sceneName) : _sceneName(sceneName) { }

	virtual void Tick() = 0;
	virtual void Render() = 0;
private:
	const char* _sceneName;
};