#include "Camera.h"

#include "Renderer.h"

using namespace Graphic;

Camera::Camera(){
	// Graphic::Camera& camera = *Core::camera;
	// 	
	

	// Core::input.
};

float Camera::getX() const{
	return position.x;
}

float Camera::getY() const{
	return position.y;
}

void Camera::setX(const float x){
	position.setX(x);
}

void Camera::setY(const float y){
	position.setY(y);
}

Camera::~Camera() = default;

void Camera::setScale(const float f){
	scale = f;
}

void Camera::trans(const float x, const float y){
	position.add(x, y);
}

float Camera::getScale() const{
	return scale;
}

Vector2D Camera::screenCenter() const{
	return Vector2D{ position };//.add(getRenderer().width / 2.0f, getRenderer().height / 2.0f);
}

void Camera::setOrtho(float width, float height){
	width /= scale;
	height /= scale;

	worldToScreen.setOrthogonal(0, 0, width, height).translate(-position.x + width / 2.0f, -position.y + height / 2.0f);  // NOLINT(clang-diagnostic-implicit-int-float-conversion)
}
