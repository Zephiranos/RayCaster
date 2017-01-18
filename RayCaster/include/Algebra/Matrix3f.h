#pragma once
#ifndef MATRIX_3F_H
#define MATRIX_3F_H

#include <cstdio>
class Matrix2f;
class Quat4f;
class Vector3f;

///////////////////////////
// 3x3 Matrix Math Header
//
// Nicolas Bordes - 10/2016
///////////////////////////

class Matrix3f
{
public:
	// Constructor
	Matrix3f(float fill = 0.f);
	Matrix3f(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
	Matrix3f(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, bool setColumns = true);
	Matrix3f(const Matrix3f& m);
	Matrix3f& operator = (const Matrix3f& m);

	// Utility
	const float& operator () (int i, int j) const;
	float& operator () (int i, int j);
	Vector3f getRow(int i) const;
	void setRow(int i, const Vector3f& v);
	Vector3f getCol(int i) const;
	void setCol(int i, const Vector3f& v);

	Matrix2f getSubMatrix2x2(int i0, int j0);
	void setSubMatrix2x2(int i0, int j0, Matrix2f m);

	operator float* ();
	void print();

	// Math
	float determinant();
	Matrix3f inverse(bool* pbIsSingular = NULL, float epsilon = 0.f);
	void transpose();
	Matrix3f transposed() const;

	static float determinant3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
	static Matrix3f ones();
	static Matrix3f identity();
	static Matrix3f rotateX(float radians);
	static Matrix3f rotateY(float radians);
	static Matrix3f rotateZ(float radians);
	static Matrix3f scaling(float sX, float sY, float sZ);
	static Matrix3f uniformScaling(float s);
	static Matrix3f rotation(const Vector3f& direction ,float radians);
	static Matrix3f rotation(const Quat4f q);

private:

	float m_elements[9];
};
/////////////////
// Operators Math
/////////////////
// Scalar multiplication
Matrix3f operator * (const Matrix3f& m, float f);
Matrix3f operator * (float f, const Matrix3f& m);

// Matrix-Vector multiplication
Vector3f operator * (const Matrix3f& m, const Vector3f& v);

// Matrix-Matrix multiplication
Matrix3f operator * (const Matrix3f& m1, const Matrix3f& m2);


#endif // MATRIX_3F_H