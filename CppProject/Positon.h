#pragma once

namespace Geom {
	class Position  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~Position();

		virtual float getX() const = 0;
		virtual float getY() const = 0;

		virtual void setX(const float x) = 0;
		virtual void setY(const float y) = 0;

		float dst2(const Position& other) const;

		float dst(const Position& other) const;

		bool within(const Position& other, const float dst) const;

		bool invalid() const;
	};
}