#include "InputCore.h"

#include <iostream>

#include "key.h"

namespace Graphic{
	class Camera;
}

InputCore::InputCore(GLFWwindow* w): window(w){
	keyBinds = new vector<KeyFunc>;
}

void InputCore::setPos(const float x, const float y){
	mousePos.set(x, y);

	for (const auto& listener : cursorListener) {
		listener(x, y);
	}
}

Geom::Vector2D& InputCore::getPos(){
	return mousePos;
}

Geom::Vector2D& InputCore::getScrollOffset(){
	return scrollOffset;
}

void InputCore::setScrollOffset(const float x, const float y){
	scrollOffset.set(x, y);

	for(const auto & listener : scrollListener){
		listener(x, y);
	}
}

bool InputCore::inbound() const{
	return isInbound;
}

void InputCore::setInbound(const bool b){
	isInbound = b;
	// std::cout << "INBOUND::" << isInbound << endl;
}

void InputCore::registerKeyShower() const{
	for(int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; i++){
		keyBinds->push_back(
			KeyFunc{ new KeyBind(i, GLFW_PRESS),
				[=](int k) -> void {
					cout << glfwGetKeyScancode(i) << endl;
					// cout << string(glfwGetKeyName(i, glfwGetKeyScancode(i))) << endl;
				}
			});
	}
}

void InputCore::update(){
	for(const auto & keyBind : *keyBinds){
		if(keyBind.bind->activated(window))keyBind.func(keyBind.bind->keyCode());
		else if(keyBind.elseFunc){
			keyBind.elseFunc(keyBind.bind->keyCode());
		}
	}
}

void InputCore::dispose(){
	delete keyBinds;
}
