#pragma once
#ifndef MATRIX_2F_H
#define MATRIX_2F_H

#include <cstdio>
class Vector2f;

///////////////////////////
// 2x2 Matrix Math Header
//
// Nicolas Bordes - 10/2016
///////////////////////////

class Matrix2f
{
public:
	// Constructors
	Matrix2f(float fill = 0.f);
	Matrix2f(float m00, float m01, float m10, float m11);
	Matrix2f(const Vector2f& v0, const Vector2f& v1, bool setColumns = true);
	Matrix2f(const Matrix2f& m);
	Matrix2f& operator = (const Matrix2f& m);

	// Utility
	const float& operator () (int i, int j) const;
	float& operator () (int i, int j);
	Vector2f getRow(int i) const;
	void setRow(int i, const Vector2f& v);
	Vector2f getCol(int i) const;
	void setCol(int i, const Vector2f& v);

	operator float* ();
	void print();

	// Math
	float determinant();
	Matrix2f inverse(bool* pbIsSingular = NULL, float epsilon = 0.f);
	void transpose();
	Matrix2f transposed() const;

	static float determinant2x2(float m00, float m01, float m10, float m11);
	static Matrix2f ones();
	static Matrix2f identity();
	static Matrix2f rotation(float degree);

private:

	float m_elements[4];
};
/////////////////
// Operators Math
/////////////////
// Scalar multiplication
Matrix2f operator * (const Matrix2f& m, float f);
Matrix2f operator * (float f, const Matrix2f& m);

// Matrix-Vector multiplication
Vector2f operator * (const Matrix2f& m, const Vector2f& v);

// Matrix-Matrix multiplication
Matrix2f operator * (const Matrix2f& m1, const Matrix2f& m2);

#endif // MATRIX_2F_H
