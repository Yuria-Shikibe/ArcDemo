
// ReSharper disable CppClassCanBeFinal
#pragma once
#include <ostream>

#include "Positon.h"
#include "Vector3D.h"

namespace Geom{
	class Matrix3D;

	class Vector2D : public Position
	{

	public:
		Vector2D(const float x, const float y);

		Vector2D();

		explicit Vector2D(const size_t hash);

		Vector2D(const Vector2D& tgt);

		Vector2D(Vector2D&& tgt) noexcept;

		~Vector2D() override;

	public:
		float x = 0, y = 0;

		Vector2D& operator=(const Vector2D& tgt);

		Vector2D& operator=(Vector2D&& tgt) noexcept;


		//All these operators will modify and return itself!
		Vector2D& operator+(const Vector2D& tgt);

		Vector2D& operator-(const Vector2D& tgt);

		Vector2D& operator*(const Vector2D& tgt);

		Vector2D& operator*(const float  val);

		Vector2D& operator/(const Vector2D& tgt);

		Vector2D& operator/(const float tgt);

		Vector2D& operator%(const Vector2D& tgt);

		Vector2D& operator%(const float tgt);

		Vector2D& set(const float ox, const float oy);

		Vector2D& set(const float val);

		Vector2D& set(const Vector2D& tgt);

		Vector2D& add(const float ox, const float oy);

		Vector2D& add(const Vector2D& other);

		Vector2D& sub(const float ox, const float oy);

		Vector2D& sub(const Vector2D& other);

		Vector2D& mul(const float ox, const float oy);

		Vector2D& mul(const float val);

		Vector2D& mul(const Vector2D& other);

		Vector2D& div(const float ox, const float oy);

		Vector2D& div(const float val);

		Vector2D& div(const Vector2D& other);

		Vector2D& mod(const float ox, const float oy);

		Vector2D& mod(const float val);

		Vector2D& mod(const Vector2D& other);

		Vector2D copy() const;

		Vector2D& setZero();

		Vector2D& setNaN();

		float getX() const override;

		float getY() const override;

		void setX(const float ox) override;

		void setY(const float oy) override;

		float length() const;

		float length2() const;

		float angle() const;

		float angle(const Vector2D& reference) const;

		Vector2D& normalize();

		Vector2D& rotateRad(const float rad);

		Vector2D& rotate(const float degree);

		/**
		 * \brief 
		 * \return 
		 */
		Vector2D& rotateRT(){
			return set(y, -x);
		}

		Vector2D& lerp(const Vector2D& tgt, const float alpha);

		Vector2D& approach(const Vector2D& target, const float alpha);

		Vector2D& setPolar(const float angDeg, const float length);

		Vector2D& setPolar(const float angDeg);

		float dot(const Vector2D& tgt) const;

		float cross(const Vector2D& tgt) const;

		Vector2D& project(const Vector2D& tgt);

		Vector2D& operator()(const float ox, const float oy);

		size_t hashCode() const;

		static size_t hashCode(const Vector2D& tgt);

		static void swap(Vector2D& lhs, Vector2D& rhs) noexcept;

		Vector2D& swap(Vector2D& tgt) noexcept;

		friend bool operator<(const Geom::Vector2D& lhs, const Geom::Vector2D& rhs) {
			if (lhs.length2() < rhs.length2()) return true;
			return false;
		}

		friend bool operator<=(const Geom::Vector2D& lhs, const Geom::Vector2D& rhs) {
			return rhs >= lhs;
		}

		friend bool operator>(const Geom::Vector2D& lhs, const Geom::Vector2D& rhs) {
			return rhs < lhs;
		}

		friend bool operator>=(const Geom::Vector2D& lhs, const Geom::Vector2D& rhs) {
			return !(lhs < rhs);
		}

		friend std::ostream& operator<<(std::ostream& os, const Geom::Vector2D& obj){
			return os << '(' << obj.x << ", " << obj.y << ')';
		}

		Vector2D& clampLength(const float min, const float max);

		Vector2D& limit(const float limit);

		Vector2D& limit2(const float limit2);

		Vector2D& scl(const float val);

		Vector2D& scl(const float ox, const float oy);

		Vector2D& clamp(const float min, const float max);

		Vector2D& setLength(const float len);

		Vector2D& setLength2(float len2);

		Vector3D expandTo3D(const float z) const;

		Vector3D expandTo3D() const;

		float angleRad() const;

		float angleExact() const;

		Vector2D& map(void(* transformer)(Vector2D&));

		Vector2D& mul(const Matrix3D& mat);
		
		Vector2D& operator*=(const Matrix3D& mat) {
			return mul(mat);
		}

		template<typename T>
		T& map(T&(*transformer)(Vector2D&));

		template<typename T>
		T map(T(*transformer)(Vector2D&));
	};

	static const Vector2D ZERO{ 0, 0 };
	static const Vector2D X{ 1, 0 };
	static const Vector2D Y{ 0, 1 };
	static Vector2D vec2_1, vec2_2, vec2_3, vec2_4, vec2_5, vec2_6; //!THREAD UNSAFE!
}
