#pragma once
#include "Matrix3D.h"

using namespace Geom;

namespace Graphic{
	class Camera{
	public:
		Matrix3D worldToScreen{};
		Matrix3D screenToWorld{};
		Vector2D position{0, 0};
		float scale = 1.0f;

		Camera();

		float getX() const;

		float getY() const;

		void setX(const float x);

		void setY(const float y);

		Camera(const Camera& other) = delete;

		Camera(Camera&& other) = delete;

		Camera& operator=(const Camera& other) = delete;

		Camera& operator=(Camera&& other) = delete;

		~Camera();

		void setScale(const float f);

		void trans(const float x, const float y);

		[[nodiscard]] float getScale() const;

		Vector2D screenCenter() const;

		void setOrtho(const float width, const float height);
	};
}

