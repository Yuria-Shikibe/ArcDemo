#include "Vector2D.h"

#include "convert.h"
#include "Mathf.h"
#include "Matrix3D.h"

Geom::Vector2D::Vector2D(const float x, const float y) : x(x), y(y) {
	}

Geom::Vector2D::Vector2D() : Vector2D(0, 0) {

	}

Geom::Vector2D::Vector2D(const size_t hash){
		set(unpackX_Float(hash), unpackY_Float(hash));
	}

Geom::Vector2D::Vector2D(const Vector2D& tgt) {
		set(tgt.x, tgt.y);
	}

Geom::Vector2D::Vector2D(Vector2D&& tgt) noexcept {
		set(tgt.x, tgt.y);
	}

Geom::Vector2D::~Vector2D() {
	}

Geom::Vector2D& Geom::Vector2D::operator=(const Vector2D& tgt) {
		return set(tgt.x, tgt.y);  // NOLINT(misc-unconventional-assign-operator)
	}

Geom::Vector2D& Geom::Vector2D::operator=(Vector2D&& tgt) noexcept {
		set(tgt.x, tgt.y);
		tgt.set(NAN);

		return *this;
	}

Geom::Vector2D& Geom::Vector2D::operator+(const Vector2D& tgt){
		return add(tgt);
	}

Geom::Vector2D& Geom::Vector2D::operator-(const Vector2D& tgt){
		return sub(tgt);
	}

Geom::Vector2D& Geom::Vector2D::operator*(const Vector2D& tgt){
		return mul(tgt);
	}

Geom::Vector2D& Geom::Vector2D::operator*(const float val){
		return scl(val);
	}

Geom::Vector2D& Geom::Vector2D::operator/(const Vector2D& tgt){
		return sub(tgt);
	}

Geom::Vector2D& Geom::Vector2D::operator/(const float tgt){
		return div(tgt, tgt);
	}

Geom::Vector2D& Geom::Vector2D::operator%(const Vector2D& tgt){
		return mod(tgt.x, tgt.y);
	}

Geom::Vector2D& Geom::Vector2D::operator%(const float tgt){
		return mod(tgt, tgt);
	}

Geom::Vector2D& Geom::Vector2D::mod(const float ox, const float oy){
	x = fmod(x, ox);
	y = fmod(y, oy);
	return *this;
}

Geom::Vector2D& Geom::Vector2D::mod(const float val){
	return mod(val, val);
}

Geom::Vector2D& Geom::Vector2D::mod(const Vector2D& other){
	return mod(other.x, other.y);
}

Geom::Vector2D& Geom::Vector2D::swap(Vector2D& tgt) noexcept{
	swap(*this, tgt);

	return *this;
}

Geom::Vector2D& Geom::Vector2D::map(void(* transformer)(Vector2D&)){
	transformer(*this);
	return *this;
}

Geom::Vector2D& Geom::Vector2D::mul(const Matrix3D& mat){
	return set(x * mat.val[0] + y * mat.val[3] + mat.val[6], x * mat.val[1] + y * mat.val[4] + mat.val[7]);
}

template <typename T>
T& Geom::Vector2D::map(T&(* transformer)(Vector2D&)){
	return transformer(*this);
}

template <typename T>
T Geom::Vector2D::map(T(* transformer)(Vector2D&)){
	return transformer(*this);
}

Geom::Vector2D Geom::Vector2D::copy() const{
	return Geom::Vector2D{ x, y };
}

Geom::Vector2D& Geom::Vector2D::setZero(){
	return set(0.0f, 0.0f);
}

Geom::Vector2D& Geom::Vector2D::setNaN(){
	return set(NAN, NAN);
}

Geom::Vector2D& Geom::Vector2D::set(const float ox, const float oy) {
	this->x = ox;
	this->y = oy;

	return *this;
}

Geom::Vector2D& Geom::Vector2D::set(const float val) {
	return set(val, val);
}

Geom::Vector2D& Geom::Vector2D::set(const Vector2D& tgt) {
	return set(tgt.x, tgt.y);
}

Geom::Vector2D& Geom::Vector2D::add(const float ox, const float oy) {
	x += ox;
	y += oy;

	return *this;
}

Geom::Vector2D& Geom::Vector2D::add(const Vector2D& other) {
	return add(other.x, other.y);
}

Geom::Vector2D& Geom::Vector2D::sub(const float ox, const float oy) {
	x -= ox;
	y -= oy;

	return *this;
}

Geom::Vector2D& Geom::Vector2D::sub(const Vector2D& other) {
	return sub(other.x, other.y);
}

Geom::Vector2D& Geom::Vector2D::mul(const float ox, const float oy) {
	x *= ox;
	y *= oy;

	return *this;
}

Geom::Vector2D& Geom::Vector2D::mul(const float val) {
	return mul(val, val);
}

Geom::Vector2D& Geom::Vector2D::mul(const Vector2D& other) {
	return mul(other.x, other.y);
}

Geom::Vector2D& Geom::Vector2D::div(const float ox, const float oy) {
	x /= ox;
	y /= oy;

	return *this;
}

Geom::Vector2D& Geom::Vector2D::div(const float val) {
	return div(val, val);
}

Geom::Vector2D& Geom::Vector2D::div(const Vector2D& other) {
	return div(other.x, other.y);
}

float Geom::Vector2D::getX() const {
	return x;
}

float Geom::Vector2D::getY() const {
	return y;
}

void Geom::Vector2D::setX(const float ox) {
	this->x = ox;
}

void Geom::Vector2D::setY(const float oy) {
	this->y = oy;
}

float Geom::Vector2D::length() const {
	return std::sqrt(length2());
}

float Geom::Vector2D::length2() const {
	return x * x + y * y;
}

float Geom::Vector2D::angle() const{
	float angle = Mathf::atan2(x, y) * Mathf::RADIANS_TO_DEGREES;
	if (angle < 0) angle += 360;
	return angle;
}

float Geom::Vector2D::angle(const Vector2D& reference) const{
	return Mathf::atan2(cross(reference), dot(reference)) * Mathf::RADIANS_TO_DEGREES;
}

Geom::Vector2D& Geom::Vector2D::normalize() {
	return div(length());
}

Geom::Vector2D& Geom::Vector2D::rotateRad(const float rad) {
	//  Matrix Multi
	//  cos rad		-sin rad	x    crx   -sry
	//	sin rad		 cos rad	y	 srx	cry
	const float cosRad = Mathf::cos(rad);
	const float sinRad = Mathf::sin(rad);

	return set(cosRad * x - sinRad * y, sinRad * x + cosRad * y);
}

Geom::Vector2D& Geom::Vector2D::rotate(const float degree) {
	return rotateRad(degree * Mathf::DEGREES_TO_RADIANS);
}

Geom::Vector2D& Geom::Vector2D::lerp(const Vector2D& tgt, const float alpha) {
	return set(x + (tgt.x - x) * alpha, y + (tgt.y - y) * alpha);
}

Geom::Vector2D& Geom::Vector2D::approach(const Vector2D& target, const float alpha) {
	float dx = x - target.x, dy = y - target.y;
	const float alpha2 = alpha * alpha;
	const float len2 = dx * dx + dy * dy;

	if (len2 > alpha2) {
		const float scl = sqrt(alpha2 / len2);
		dx *= scl;
		dy *= scl;

		return sub(dx, dy);
	}

	return set(target);
}

Geom::Vector2D& Geom::Vector2D::setPolar(const float angDeg, const float length) {
	return set(length * Mathf::cos(angDeg * Mathf::DEGREES_TO_RADIANS), length * Mathf::sin(angDeg * Mathf::DEGREES_TO_RADIANS));
}

Geom::Vector2D& Geom::Vector2D::setPolar(const float angDeg){
	return setPolar(angDeg, length());
}

float Geom::Vector2D::dot(const Vector2D& tgt) const {
	return x * tgt.x + y * tgt.y;
}

float Geom::Vector2D::cross(const Vector2D& tgt) const {
	return x * tgt.y - y * tgt.x;
}

Geom::Vector2D& Geom::Vector2D::project(const Vector2D& tgt) {
	return set(tgt).mul(dot(tgt) / length() / tgt.length2());
}

Geom::Vector2D& Geom::Vector2D::operator()(const float ox, const float oy){
	return set(ox, oy);
}

size_t Geom::Vector2D::hashCode() const {
	return pack(x, y);
}

size_t Geom::Vector2D::hashCode(const Vector2D& tgt){
	return tgt.hashCode();
}

void Geom::Vector2D::swap(Geom::Vector2D& lhs, Geom::Vector2D& rhs) noexcept{
	using std::swap;
	const float x1 = lhs.x;
	const float y1 = lhs.y;

	lhs.x = rhs.x;
	lhs.y = rhs.y;
	rhs.x = x1;
	rhs.y = y1;
}

bool operator==(const Geom::Vector2D& lhs, const Geom::Vector2D& rhs){
	return lhs.hashCode() == rhs.hashCode();
}

bool operator!=(const Geom::Vector2D& lhs, const Geom::Vector2D& rhs){
	return lhs.hashCode() != rhs.hashCode();
}

Geom::Vector3D Geom::Vector2D::expandTo3D(const float z) const{
		return Vector3D{ x, y, z };
	}

Geom::Vector3D Geom::Vector2D::expandTo3D() const{
		return expandTo3D(0);
	}

Geom::Vector2D& Geom::Vector2D::clampLength(const float min, const float max) {
	const float len2 = length2();
	if (len2 >= max * max) {
		return limit(max);
	}
	else if (len2 <= min * min) {
		return setLength(min);
	}

	return *this;
}

Geom::Vector2D& Geom::Vector2D::limit(const float limit) {
	return limit2(limit * limit);
}

Geom::Vector2D& Geom::Vector2D::limit2(const float limit2) {
	const float len2 = length2();
	if (len2 > limit2) {
		return scl(sqrt(limit2 / len2));
	}
	return *this;
}

Geom::Vector2D& Geom::Vector2D::scl(const float val) {
	return scl(val, val);
}

Geom::Vector2D& Geom::Vector2D::scl(const float ox, const float oy) {
	x *= ox;
	y *= oy;
	return *this;
}

Geom::Vector2D& Geom::Vector2D::clamp(const float min, const float max) {
	const float len2 = length2();
	if (len2 == 0) return *this;  // NOLINT(clang-diagnostic-float-equal)
	const float max2 = max * max;
	if (len2 > max2) return scl(sqrt(max2 / len2));
	const float min2 = min * min;
	if (len2 < min2) return scl(sqrt(min2 / len2));
	return *this;
}

Geom::Vector2D& Geom::Vector2D::setLength(const float len) {
	return setLength2(len * len);
}

Geom::Vector2D& Geom::Vector2D::setLength2(const float len2) {
	const float oldLen2 = length2();
	return (oldLen2 == 0 || oldLen2 == len2) ? *this : scl(sqrt(len2 / oldLen2));  // NOLINT(clang-diagnostic-float-equal)
}

float Geom::Vector2D::angleRad() const {
	return Mathf::atan2(y, x);
}

float Geom::Vector2D::angleExact() const {
	return Mathf::atan2(y, x) * Mathf::DEGREES_TO_RADIANS;
}

