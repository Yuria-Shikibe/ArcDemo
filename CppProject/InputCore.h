#pragma once
#include <functional>
#include <GLFW/glfw3.h>

#include "ApplicationListener.h"
#include "Vector2D.h"

struct KeyFunc;
using namespace std;

class InputCore final : public virtual ApplicationListener
{

public:
	vector<function<void(float, float)>> scrollListener;
	vector<function<void(float, float)>> cursorListener;
	vector<KeyFunc>* keyBinds;

protected:
	GLFWwindow* window;
	bool isInbound = false;
	Geom::Vector2D mousePos;
	Geom::Vector2D scrollOffset;

public:
	explicit InputCore(GLFWwindow* w);

	void setPos(const float x, const float y);

	Geom::Vector2D& getPos();

	Geom::Vector2D& getScrollOffset();

	void setScrollOffset(const float x, const float y);

	[[nodiscard]] bool inbound() const;

	void setInbound(const bool b);

	void registerKeyShower() const;

	void update() override;

	void dispose() override;

	void registerKeyBind(const KeyFunc& keyFunc) const{
		keyBinds->push_back(keyFunc);
	}
};

