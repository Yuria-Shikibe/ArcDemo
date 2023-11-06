#include "Matrix3D.h"
#include <ostream>
#include <sstream>

#include "Mathf.h"

Geom::Matrix3D::Matrix3D(){
	idt();
}

Geom::Matrix3D::Matrix3D(const float values[]){
	set(values);
}

Geom::Matrix3D::Matrix3D(const std::array<float, 9>& arr){
	set(arr.data());
}

void Geom::Matrix3D::mul(float mat_a[], float mat_b[]){
	const float v00 = mat_a[M00] * mat_b[M00] + mat_a[M01] * mat_b[M10] + mat_a[M02] * mat_b[M20];
	const float v01 = mat_a[M00] * mat_b[M01] + mat_a[M01] * mat_b[M11] + mat_a[M02] * mat_b[M21];
	const float v02 = mat_a[M00] * mat_b[M02] + mat_a[M01] * mat_b[M12] + mat_a[M02] * mat_b[M22];

	const float v10 = mat_a[M10] * mat_b[M00] + mat_a[M11] * mat_b[M10] + mat_a[M12] * mat_b[M20];
	const float v11 = mat_a[M10] * mat_b[M01] + mat_a[M11] * mat_b[M11] + mat_a[M12] * mat_b[M21];
	const float v12 = mat_a[M10] * mat_b[M02] + mat_a[M11] * mat_b[M12] + mat_a[M12] * mat_b[M22];

	const float v20 = mat_a[M20] * mat_b[M00] + mat_a[M21] * mat_b[M10] + mat_a[M22] * mat_b[M20];
	const float v21 = mat_a[M20] * mat_b[M01] + mat_a[M21] * mat_b[M11] + mat_a[M22] * mat_b[M21];
	const float v22 = mat_a[M20] * mat_b[M02] + mat_a[M21] * mat_b[M12] + mat_a[M22] * mat_b[M22];

	mat_a[M00] = v00;
	mat_a[M10] = v10;
	mat_a[M20] = v20;
	mat_a[M01] = v01;
	mat_a[M11] = v11;
	mat_a[M21] = v21;
	mat_a[M02] = v02;
	mat_a[M12] = v12;
	mat_a[M22] = v22;
}

std::ostream& Geom::operator<<(std::ostream& os, const Matrix3D& obj){
	return os << obj.toString();
}

Geom::Matrix3D::Matrix3D(const Matrix3D& other){  // NOLINT(cppcoreguidelines-pro-type-member-init)
	set(other);
}

Geom::Matrix3D::Matrix3D(Matrix3D&& other) noexcept{  // NOLINT(cppcoreguidelines-pro-type-member-init)
	set(other);
}

Geom::Matrix3D& Geom::Matrix3D::operator=(const Matrix3D& other){
	if (this == &other) return *this;
	set(other);
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::operator=(Matrix3D&& other) noexcept{
	if (this == &other) return *this;
	set(other);
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::setOrthogonal(const float x, const float y, const float width, const float height){
	const float right = x + width, top = y + height;

	const float x_orth = 2 / (right - x);
	const float y_orth = 2 / (top - y);

	const float tx = -(right + x) / (right - x);
	const float ty = -(top + y) / (top - y);

	val[M00] = x_orth;
	val[M11] = y_orth;

	val[M02] = tx;
	val[M12] = ty;
	val[M22] = 1.0f;

	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::idt(){
	val[M00] = 1;
	val[M10] = 0;
	val[M20] = 0;
	val[M01] = 0;
	val[M11] = 1;
	val[M21] = 0;
	val[M02] = 0;
	val[M12] = 0;
	val[M22] = 1;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::mul(const Matrix3D& m){
	const float v00 = val[M00] * m.val[M00] + val[M01] * m.val[M10] + val[M02] * m.val[M20];
	const float v01 = val[M00] * m.val[M01] + val[M01] * m.val[M11] + val[M02] * m.val[M21];
	const float v02 = val[M00] * m.val[M02] + val[M01] * m.val[M12] + val[M02] * m.val[M22];

	const float v10 = val[M10] * m.val[M00] + val[M11] * m.val[M10] + val[M12] * m.val[M20];
	const float v11 = val[M10] * m.val[M01] + val[M11] * m.val[M11] + val[M12] * m.val[M21];
	const float v12 = val[M10] * m.val[M02] + val[M11] * m.val[M12] + val[M12] * m.val[M22];

	const float v20 = val[M20] * m.val[M00] + val[M21] * m.val[M10] + val[M22] * m.val[M20];
	const float v21 = val[M20] * m.val[M01] + val[M21] * m.val[M11] + val[M22] * m.val[M21];
	const float v22 = val[M20] * m.val[M02] + val[M21] * m.val[M12] + val[M22] * m.val[M22];

	val[M00] = v00;
	val[M10] = v10;
	val[M20] = v20;
	val[M01] = v01;
	val[M11] = v11;
	val[M21] = v21;
	val[M02] = v02;
	val[M12] = v12;
	val[M22] = v22;

	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::mulLeft(const Matrix3D& m){
	const float v00 = m.val[M00] * val[M00] + m.val[M01] * val[M10] + m.val[M02] * val[M20];
	const float v01 = m.val[M00] * val[M01] + m.val[M01] * val[M11] + m.val[M02] * val[M21];
	const float v02 = m.val[M00] * val[M02] + m.val[M01] * val[M12] + m.val[M02] * val[M22];

	const float v10 = m.val[M10] * val[M00] + m.val[M11] * val[M10] + m.val[M12] * val[M20];
	const float v11 = m.val[M10] * val[M01] + m.val[M11] * val[M11] + m.val[M12] * val[M21];
	const float v12 = m.val[M10] * val[M02] + m.val[M11] * val[M12] + m.val[M12] * val[M22];

	const float v20 = m.val[M20] * val[M00] + m.val[M21] * val[M10] + m.val[M22] * val[M20];
	const float v21 = m.val[M20] * val[M01] + m.val[M21] * val[M11] + m.val[M22] * val[M21];
	const float v22 = m.val[M20] * val[M02] + m.val[M21] * val[M12] + m.val[M22] * val[M22];

	val[M00] = v00;
	val[M10] = v10;
	val[M20] = v20;
	val[M01] = v01;
	val[M11] = v11;
	val[M21] = v21;
	val[M02] = v02;
	val[M12] = v12;
	val[M22] = v22;

	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::setToRotation(const float degrees){
	return setToRotationRad(Mathf::DEGREES_TO_RADIANS * degrees);
}

Geom::Matrix3D& Geom::Matrix3D::setToRotationRad(const float radians){
	const float cos = Mathf::cos(radians);
	const float sin = Mathf::sin(radians);

	val[M00] = cos;
	val[M10] = sin;
	val[M20] = 0;

	val[M01] = -sin;
	val[M11] = cos;
	val[M21] = 0;

	val[M02] = 0;
	val[M12] = 0;
	val[M22] = 1;

	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::setToRotation(const Geom::Vector3D axis, const float degrees){
	return setToRotation(axis, Mathf::cosDeg(degrees), Mathf::sinDeg(degrees));
}

Geom::Matrix3D& Geom::Matrix3D::setToRotation(const Geom::Vector3D axis, const float cos, const float sin){
	const float oc = 1.0f - cos;
	val[M00] = oc * axis.x * axis.x + cos;
	val[M10] = oc * axis.x * axis.y - axis.z * sin;
	val[M20] = oc * axis.z * axis.x + axis.y * sin;
	val[M01] = oc * axis.x * axis.y + axis.z * sin;
	val[M11] = oc * axis.y * axis.y + cos;
	val[M21] = oc * axis.y * axis.z - axis.x * sin;
	val[M02] = oc * axis.z * axis.x - axis.y * sin;
	val[M12] = oc * axis.y * axis.z + axis.x * sin;
	val[M22] = oc * axis.z * axis.z + cos;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::setToTranslation(const float x, const float y){
	val[M00] = 1;
	val[M10] = 0;
	val[M20] = 0;

	val[M01] = 0;
	val[M11] = 1;
	val[M21] = 0;

	val[M02] = x;
	val[M12] = y;
	val[M22] = 1;

	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::setToTranslation(const Geom::Vector2D& translation){
	val[M00] = 1;
	val[M10] = 0;
	val[M20] = 0;

	val[M01] = 0;
	val[M11] = 1;
	val[M21] = 0;

	val[M02] = translation.x;
	val[M12] = translation.y;
	val[M22] = 1;

	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::setToScaling(const float scaleX, const float scaleY){
	val[M00] = scaleX;
	val[M10] = 0;
	val[M20] = 0;
	val[M01] = 0;
	val[M11] = scaleY;
	val[M21] = 0;
	val[M02] = 0;
	val[M12] = 0;
	val[M22] = 1;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::setToScaling(const Geom::Vector2D& scale){
	val[M00] = scale.x;
	val[M10] = 0;
	val[M20] = 0;
	val[M01] = 0;
	val[M11] = scale.y;
	val[M21] = 0;
	val[M02] = 0;
	val[M12] = 0;
	val[M22] = 1;
	return *this;
}

std::string Geom::Matrix3D::toString() const{
	std::stringstream ss;
	ss << "[" << val[M00] << "|" << val[M01] << "|" << val[M02] << "]\n" //
		<< "[" << val[M10] << "|" << val[M11] << "|" << val[M12] << "]\n" //
		<< "[" << val[M20] << "|" << val[M21] << "|" << val[M22] << "]";

	return ss.str();
}

float Geom::Matrix3D::det() const{
	return val[M00] * val[M11] * val[M22] + val[M01] * val[M12] * val[M20] + val[M02] * val[M10] * val[M21] - val[M00]
		* val[M12] * val[M21] - val[M01] * val[M10] * val[M22] - val[M02] * val[M11] * val[M20];
}

Geom::Matrix3D& Geom::Matrix3D::inv(){
	const float detV = det();
	if (detV == 0) throw std::exception("Can't invert a singular matrix");  // NOLINT(clang-diagnostic-float-equal)

	const float inv_det = 1.0f / detV;

	tmp[M00] = val[M11] * val[M22] - val[M21] * val[M12];
	tmp[M10] = val[M20] * val[M12] - val[M10] * val[M22];
	tmp[M20] = val[M10] * val[M21] - val[M20] * val[M11];
	tmp[M01] = val[M21] * val[M02] - val[M01] * val[M22];
	tmp[M11] = val[M00] * val[M22] - val[M20] * val[M02];
	tmp[M21] = val[M20] * val[M01] - val[M00] * val[M21];
	tmp[M02] = val[M01] * val[M12] - val[M11] * val[M02];
	tmp[M12] = val[M10] * val[M02] - val[M00] * val[M12];
	tmp[M22] = val[M00] * val[M11] - val[M10] * val[M01];

	val[M00] = inv_det * tmp[M00];
	val[M10] = inv_det * tmp[M10];
	val[M20] = inv_det * tmp[M20];
	val[M01] = inv_det * tmp[M01];
	val[M11] = inv_det * tmp[M11];
	val[M21] = inv_det * tmp[M21];
	val[M02] = inv_det * tmp[M02];
	val[M12] = inv_det * tmp[M12];
	val[M22] = inv_det * tmp[M22];

	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::set(const Matrix3D& mat){
	std::copy(&mat.val[0], &mat.val[8], &val[0]);
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::set(const float values[]){
	// if (size < 9)throw std::exception("Cannot Construct A Matrix Without 9 Numbers.");
	std::copy(&values[0], &values[8], &val[0]);
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::trn(const Geom::Vector2D& vector){
	val[M02] += vector.x;
	val[M12] += vector.y;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::trn(const float x, const float y){
	val[M02] += x;
	val[M12] += y;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::trn(const Geom::Vector3D vector){
	val[M02] += vector.x;
	val[M12] += vector.y;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::translate(const float x, const float y){
	tmp[M00] = 1;
	tmp[M10] = 0;
	tmp[M20] = 0;

	tmp[M01] = 0;
	tmp[M11] = 1;
	tmp[M21] = 0;

	tmp[M02] = x;
	tmp[M12] = y;
	tmp[M22] = 1;
	mul(val, tmp);
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::translate(const Geom::Vector2D& translation){
	tmp[M00] = 1;
	tmp[M10] = 0;
	tmp[M20] = 0;

	tmp[M01] = 0;
	tmp[M11] = 1;
	tmp[M21] = 0;

	tmp[M02] = translation.x;
	tmp[M12] = translation.y;
	tmp[M22] = 1;
	mul(val, tmp);
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::rotate(const float degrees){
	return rotateRad(Mathf::DEGREES_TO_RADIANS * degrees);
}

Geom::Matrix3D& Geom::Matrix3D::rotateRad(const float radians){
	if (radians == 0) return *this;  // NOLINT(clang-diagnostic-float-equal)
	const float cos = Mathf::cos(radians);
	const float sin = Mathf::sin(radians);

	tmp[M00] = cos;
	tmp[M10] = sin;
	tmp[M20] = 0;

	tmp[M01] = -sin;
	tmp[M11] = cos;
	tmp[M21] = 0;

	tmp[M02] = 0;
	tmp[M12] = 0;
	tmp[M22] = 1;
	mul(val, tmp);
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::scale(const float scaleX, const float scaleY){
	tmp[M00] = scaleX;
	tmp[M10] = 0;
	tmp[M20] = 0;
	tmp[M01] = 0;
	tmp[M11] = scaleY;
	tmp[M21] = 0;
	tmp[M02] = 0;
	tmp[M12] = 0;
	tmp[M22] = 1;
	mul(val, tmp);
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::scale(const Geom::Vector2D& scale){
	tmp[M00] = scale.x;
	tmp[M10] = 0;
	tmp[M20] = 0;
	tmp[M01] = 0;
	tmp[M11] = scale.y;
	tmp[M21] = 0;
	tmp[M02] = 0;
	tmp[M12] = 0;
	tmp[M22] = 1;
	mul(val, tmp);
	return *this;
}

// std::array<float, 9> Geom::Matrix3D::getValues() const{
// 	return std::array<float, 9>{ val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7], val[8] };
// }

Geom::Vector2D& Geom::Matrix3D::getTranslation(Vector2D& position) const{
	position.x = val[M02];
	position.y = val[M12];
	return position;
}

Geom::Vector2D& Geom::Matrix3D::getScale(Vector2D& scale) const{
	scale.x = sqrt(val[M00] * val[M00] + val[M01] * val[M01]);
	scale.y = sqrt(val[M10] * val[M10] + val[M11] * val[M11]);
	return scale;
}

float Geom::Matrix3D::getRotation() const{
	return Mathf::RADIANS_TO_DEGREES * Mathf::atan2(val[M10], val[M00]);
}

float Geom::Matrix3D::getRotationRad() const{
	return Mathf::atan2(val[M10], val[M00]);
}

Geom::Matrix3D& Geom::Matrix3D::scl(const float scale){
	val[M00] *= scale;
	val[M11] *= scale;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::scl(const Geom::Vector2D& scale){
	val[M00] *= scale.x;
	val[M11] *= scale.y;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::scl(const Geom::Vector3D scale){
	val[M00] *= scale.x;
	val[M11] *= scale.y;
	return *this;
}

Geom::Matrix3D& Geom::Matrix3D::transpose(){
	// Where MXY you do not have to change MXX

	const float v01 = val[M10];
	const float v02 = val[M20];
	const float v10 = val[M01];
	const float v12 = val[M21];
	const float v20 = val[M02];
	const float v21 = val[M12];
	val[M01] = v01;
	val[M02] = v02;
	val[M10] = v10;
	val[M12] = v12;
	val[M20] = v20;
	val[M21] = v21;
	return *this;
}
