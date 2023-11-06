#include "Positon.h"
#include "Vector2D.h"
#include <cmath>


namespace Geom {
	Position::~Position() = default;

	float Position::dst2(const Position& other) const {
		const float dx = getX() - other.getX();
		const float dy = getY() - other.getY();

		return dx * dx + dy * dy;
	}

	float Position::dst(const Position& other) const {
		return std::sqrt(dst2(other));
	}

	bool Position::within(const Position& other, const float dst) const {
		return dst2(other) < dst * dst;
	}

	bool Position::invalid() const {
		return !(isnan(getX()) || isnan(getY()));
	}
}