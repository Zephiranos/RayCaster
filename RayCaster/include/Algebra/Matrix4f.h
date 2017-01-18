#pragma once
#ifndef MATRIX_4F_H
#define MATRIX_4F_H

#include <cstdio>

class Matrix2f;
class Matrix3f;
class Quat4f;
class Vector3f;
class Vector4f;

///////////////////////////
// 4x4 Matrix Math Header
//
// Nicolas Bordes - 10/2016
///////////////////////////

class Matrix4f
{
public:
	// Constructor
	Matrix4f(float fill = 0.f);
	Matrix4f(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
	Matrix4f(const Vector4f& v0, const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, bool setColumns = true);
	Matrix4f(const Matrix4f& m);
	Matrix4f& operator = (const Matrix4f& m);

	// Utility
	const float& operator () (int i, int j) const;
	float& operator () (int i, int j);
	Vector4f getRow(int i) const;
	void setRow(int i, const Vector4f& v);
	Vector4f getCol(int i) const;
	void setCol(int i, const Vector4f& v);

	Matrix2f getSubMatrix2x2(int i0, int j0);
	void setSubMatrix2x2(int i0, int j0, Matrix2f m);

	Matrix3f getSubMatrix3x3(int i0, int j0);
	void setSubMatrix3x3(int i0, int j0, Matrix3f m);

	operator float* ();
	void print();

	// Math
	float determinant();
	Matrix4f inverse(bool* pbIsSingular = NULL, float epsilon = 0.f);
	void transpose();
	Matrix4f transposed() const;

	static float determinant4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
	static Matrix4f ones();
	static Matrix4f identity();
	static Matrix4f translation(float x, float y, float z);
	static Matrix4f translation(const Vector3f& t);
	static Matrix4f rotateX(float radians);
	static Matrix4f rotateY(float radians);
	static Matrix4f rotateZ(float radians);
	static Matrix4f scaling(float sX, float sY, float sZ);
	static Matrix4f uniformScaling(float s);
	static Matrix4f rotation(const Vector3f& direction, float radians);
	static Matrix4f lookat(const Vector3f& eye, const Vector3f& center, const Vector3f& up);
	static Matrix4f orthographicProjection(float width, float height, float zNear, float zFar, bool directX);
	static Matrix4f orthographicProjection(float left, float right, float bot, float top, float zNear, float zFar, bool directX);
	static Matrix4f perspectiveProjection(float left, float right, float bot, float top, float zNear, float zFar, bool directX);
	static Matrix4f perspectiveProjection(float fovYRadians, float aspect, float zNear, float zFar, bool directX);
	static Matrix4f infinitePerspectiveProjection(float left, float right, float bot, float top, float zNear, float zFar, bool directX);
	static Matrix4f rotation(const Quat4f q);

private:

	float m_elements[16];
};
/////////////////
// Operators Math
/////////////////
// Scalar multiplication
Matrix4f operator * (const Matrix4f& m, float f);
Matrix4f operator * (float f, const Matrix4f& m);

// Matrix-Vector multiplication
Vector4f operator * (const Matrix4f& m, const Vector4f& v);

// Matrix-Matrix multiplication
Matrix4f operator * (const Matrix4f& m1, const Matrix4f& m2);

#endif // MATRIX_4F_H