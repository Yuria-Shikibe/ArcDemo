#pragma once
#include <array>
#include "Vector2D.h"

namespace Geom{
    class Matrix3D
    {
    private: float tmp[9] = { 0 };

    public:
        inline static constexpr int M00 = 0;
        inline static constexpr int M01 = 3;
        inline static constexpr int M02 = 6;
        inline static constexpr int M10 = 1;
        inline static constexpr int M11 = 4;
        inline static constexpr int M12 = 7;
        inline static constexpr int M20 = 2;
        inline static constexpr int M21 = 5;
        inline static constexpr int M22 = 8;
        float val[9]{};


        Matrix3D();

        explicit Matrix3D(const float values[]);

        explicit Matrix3D(const std::array<float, 9>& arr);

    private:
        static void mul(float mat_a[], float mat_b[]);

    public:
        friend std::ostream& operator<<(std::ostream& os, const Matrix3D& obj);

        Matrix3D(const Matrix3D& other);

        Matrix3D(Matrix3D&& other) noexcept;

        Matrix3D& operator=(const Matrix3D& other);

        Matrix3D& operator=(Matrix3D&& other) noexcept;

        [[nodiscard]] const float* getVal() const{
            return val;
        }


        friend bool operator==(const Matrix3D& lhs, const Matrix3D& rhs){
            return std::equal(&lhs.val[0], &lhs.val[8], &rhs.val[0]);
        }

        friend bool operator!=(const Matrix3D& lhs, const Matrix3D& rhs){
            return !(lhs == rhs);
        }

        ~Matrix3D() = default;

        friend Vector2D& operator*(const Matrix3D& mat, Vector2D& vec2) {
            return vec2.mul(mat);
        }

        friend Matrix3D& operator*(const Matrix3D& lhs, Matrix3D& rhs) {
            return rhs.mulLeft(lhs);
        }

    	Matrix3D& operator*=(const Matrix3D& lhs) {
            return mulLeft(lhs);
        }

        Matrix3D& operator~() {
            return inv();
        }

        float operator*() const {
            return det();
        }

        /** Sets this matrix to an orthographic projection. */
        Matrix3D& setOrthogonal(const float x, const float y, const float width, const float height);

        /**
         * Sets this matrix to the identity matrix
         * @return This matrix for the purpose of chaining operations.
         */
        Matrix3D& idt();

        /**
         * Post multiplies this matrix with the provided matrix and stores the result in this matrix. For example:
         *
         * <pre>
         * A.mul(B) results in A := AB
         * </pre>
         * @param m Matrix to multiply by.
         * @return This matrix for the purpose of chaining operations together.
         */
        Matrix3D& mul(const Matrix3D& m);

        /**
         * Premultiplies this matrix with the provided matrix and stores the result in this matrix. For example:
         *
         * <pre>
         * A.mulLeft(B) results in A := BA
         * </pre>
         * @param m The other Matrix to multiply by
         * @return This matrix for the purpose of chaining operations.
         */
        Matrix3D& mulLeft(const Matrix3D& m);

        /**
         * Sets this matrix to a rotation matrix that will rotate any vector in counter-clockwise direction around the z-axis.
         * @param degrees the angle in degrees.
         * @return This matrix for the purpose of chaining operations.
         */
        Matrix3D& setToRotation(const float degrees);

        /**
         * Sets this matrix to a rotation matrix that will rotate any vector in counter-clockwise direction around the z-axis.
         * @param radians the angle in radians.
         * @return This matrix for the purpose of chaining operations.
         */
        Matrix3D& setToRotationRad(const float radians);

        Matrix3D& setToRotation(const Vector3D axis, const float degrees);

        Matrix3D& setToRotation(const Vector3D axis, const float cos, const float sin);

        Matrix3D& setToTranslation(const float x, const float y);

        /**
         * Sets this matrix to a translation matrix.
         * @param translation The translation vector.
         * @return This matrix for the purpose of chaining operations.
         */
        Matrix3D& setToTranslation(const Vector2D& translation);

        /**
         * Sets this matrix to a scaling matrix.
         * @param scaleX the scale in x
         * @param scaleY the scale in y
         * @return This matrix for the purpose of chaining operations.
         */
        Matrix3D& setToScaling(const float scaleX, const float scaleY);

        /**
         * Sets this matrix to a scaling matrix.
         * @param scale The scale vector.
         * @return This matrix for the purpose of chaining operations.
         */
        Matrix3D& setToScaling(const Vector2D& scale);

        std::string toString() const;

        /** @return The determinant of this matrix */
        float det() const;

        /**
         * Inverts this matrix given that the determinant is != 0.
         * @return This matrix for the purpose of chaining operations.
         * @throws ArcRuntimeException if the matrix is singular (not invertible)
         */
        Matrix3D& inv();

        /**
         * Copies the values from the provided matrix to this matrix.
         * @param mat The matrix to copy.
         * @return This matrix for the purposes of chaining.
         */
        Matrix3D& set(const Matrix3D& mat);

        // template <size_t size>
        Matrix3D& set(const float values[]);

        /**
         * Adds a translational component to the matrix in the 3rd column. The other columns are untouched.
         * @param vector The translation vector.
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& trn(const Vector2D& vector);

        /**
         * Adds a translational component to the matrix in the 3rd column. The other columns are untouched.
         * @param x The x-component of the translation vector.
         * @param y The y-component of the translation vector.
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& trn(const float x, const float y);

        /**
         * Adds a translational component to the matrix in the 3rd column. The other columns are untouched.
         * @param vector The translation vector. (The z-component of the vector is ignored because this is a 3x3 matrix)
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& trn(const Vector3D vector);

        /**
         * Postmultiplies this matrix by a translation matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         * @param x The x-component of the translation vector.
         * @param y The y-component of the translation vector.
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& translate(const float x, const float y);

        /**
         * Postmultiplies this matrix by a translation matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         * @param translation The translation vector.
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& translate(const Vector2D& translation);

        /**
         * Postmultiplies this matrix with a (counter-clockwise) rotation matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         * @param degrees The angle in degrees
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& rotate(const float degrees);

        /**
         * Postmultiplies this matrix with a (counter-clockwise) rotation matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         * @param radians The angle in radians
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& rotateRad(const float radians);

        /**
         * Postmultiplies this matrix with a scale matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         * @param scaleX The scale in the x-axis.
         * @param scaleY The scale in the y-axis.
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& scale(const float scaleX, const float scaleY);

        /**
         * Postmultiplies this matrix with a scale matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         * @param scale The vector to scale the matrix by.
         * @return This matrix for the purpose of chaining.
         */
        Matrix3D& scale(const Vector2D& scale);

        /**
         * Get the values in this matrix.
         * @return The float values that make up this matrix in column-major order.
         */
        // std::array<float, 9> getValues() const;

        Vector2D& getTranslation(Vector2D& position) const;

        Vector2D& getScale(Vector2D& scale) const;

        float getRotation() const;

        float getRotationRad() const;

        /**
         * Scale the matrix in the both the x and y components by the scalar value.
         * @param scale The single value that will be used to scale both the x and y components.
         * @return This matrix for the purpose of chaining methods together.
         */
        Matrix3D& scl(const float scale);

        /**
         * Scale this matrix using the x and y components of the vector but leave the rest of the matrix alone.
         * @param scale The {@link Vector3D} to use to scale this matrix.
         * @return This matrix for the purpose of chaining methods together.
         */
        Matrix3D& scl(const Vector2D& scale);

        /**
         * Scale this matrix using the x and y components of the vector but leave the rest of the matrix alone.
         * @param scale The {@link Vector3D} to use to scale this matrix. The z component will be ignored.
         * @return This matrix for the purpose of chaining methods together.
         */
        Matrix3D& scl(const Vector3D scale);

        /**
         * Transposes the current matrix.
         * @return This matrix for the purpose of chaining methods together.
         */
        Matrix3D& transpose();
    };
}
