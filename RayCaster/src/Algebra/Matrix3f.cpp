#include "Matrix3f.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include "Matrix2f.h"
#include "Quat4f.h"
#include "Vector3f.h"

/////////////////////////////////
// 3x3 Matrix Math Implementation
//
// Nicolas Bordes - 10/2016
/////////////////////////////////

///////////////
// Constructors
///////////////
#pragma region Constructors

Matrix3f::Matrix3f(float fill)
{
	for (int i = 0; i < 9; ++i)
	{
		m_elements[i] = fill;
	}
}

Matrix3f::Matrix3f(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	m_elements[0] = m00;
	m_elements[1] = m01;
	m_elements[2] = m02;

	m_elements[3] = m10;
	m_elements[4] = m11;
	m_elements[5] = m12;

	m_elements[6] = m20;
	m_elements[7] = m21;
	m_elements[8] = m22;
}

Matrix3f::Matrix3f(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, bool setColumns)
{
	if (setColumns)
	{
		setCol(0, v0);
		setCol(1, v1);
		setCol(2, v2);
	}
	else
	{
		setRow(0, v0);
		setRow(1, v1);
		setRow(2, v2);
	}
}

Matrix3f::Matrix3f(const Matrix3f& m)
{
	memcpy(m_elements, m.m_elements, 9 * sizeof(float));
}

Matrix3f& Matrix3f::operator = (const Matrix3f& m)
{
	if (this != &m)
	{
		memcpy(m_elements, m.m_elements, 9 * sizeof(float));
	}
	return *this;
}
#pragma endregion
//////////
// Utility
//////////
#pragma region Utility

const float& Matrix3f::operator () (int i, int j) const
{
	return m_elements[i * 3 + j];
}

float& Matrix3f::operator () (int i, int j)
{
	return m_elements[i * 3 + j];
}

Vector3f Matrix3f::getRow(int i) const
{
	return Vector3f(m_elements[i * 3], m_elements[i * 3 + 1], m_elements[i * 3 + 2]);
}

void Matrix3f::setRow(int i, const Vector3f& v)
{
	m_elements[i * 3] = v.x();
	m_elements[i * 3 + 1] = v.y();
	m_elements[i * 3 + 2] = v.z();
}

Vector3f Matrix3f::getCol(int i) const
{
	return Vector3f(m_elements[i], m_elements[i + 3], m_elements[i + 6]);
}

void Matrix3f::setCol(int i, const Vector3f& v)
{
	m_elements[i * 3] = v.x();
	m_elements[i * 3 + 1] = v.y();
	m_elements[i * 3 + 2] = v.z();
}

Matrix2f Matrix3f::getSubMatrix2x2(int i0, int j0)
{
	Matrix2f out;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			out(i, j) = (*this)(i + i0, j + j0);
		}
	}

	return out;
}

void Matrix3f::setSubMatrix2x2(int i0, int j0, Matrix2f m)
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			(*this)(i + i0, j + j0) = m(i, j);
		}
	}
}

Matrix3f::operator float* ()
{
	return m_elements;
}

void Matrix3f::print()
{
	printf("[ %.4f %.4f %.4f ]\n[ %.4f %.4f %.4f ]\n[ %.4f %.4f %.4f ]\n",
		m_elements[0], m_elements[1], m_elements[2],
		m_elements[3], m_elements[4], m_elements[5],
		m_elements[6], m_elements[7], m_elements[8]);
}
#pragma endregion
///////
// Math
///////
#pragma region Math

float Matrix3f::determinant()
{
	return Matrix3f::determinant3x3
	(
		m_elements[0], m_elements[1], m_elements[2],
		m_elements[3], m_elements[4], m_elements[5],
		m_elements[6], m_elements[7], m_elements[8]
	);
}

Matrix3f Matrix3f::inverse(bool* pbIsSingular, float epsilon)
{
	float m00 = m_elements[0];
	float m10 = m_elements[3];
	float m20 = m_elements[6];

	float m01 = m_elements[1];
	float m11 = m_elements[4];
	float m21 = m_elements[7];

	float m02 = m_elements[2];
	float m12 = m_elements[5];
	float m22 = m_elements[8];

	float cofactor00 = Matrix2f::determinant2x2(m11, m12, m21, m22);
	float cofactor01 = -Matrix2f::determinant2x2(m10, m12, m20, m22);
	float cofactor02 = Matrix2f::determinant2x2(m10, m11, m20, m21);

	float cofactor10 = -Matrix2f::determinant2x2(m01, m02, m21, m22);
	float cofactor11 = Matrix2f::determinant2x2(m00, m02, m20, m22);
	float cofactor12 = -Matrix2f::determinant2x2(m00, m01, m20, m21);

	float cofactor20 = Matrix2f::determinant2x2(m01, m02, m11, m12);
	float cofactor21 = -Matrix2f::determinant2x2(m00, m02, m10, m12);
	float cofactor22 = Matrix2f::determinant2x2(m00, m01, m10, m11);

	float determinant = m00 * cofactor00 + m01 * cofactor01 + m02 * cofactor02;

	bool isSingular(fabs(determinant) < epsilon);
	if (isSingular)
	{
		if (pbIsSingular != NULL)
		{
			*pbIsSingular = true;
		}
		return Matrix3f();
	}
	else
	{
		if (pbIsSingular != NULL)
		{
			*pbIsSingular = false;
		}

		float recDeterminant = 1.0 / determinant;
		return recDeterminant * Matrix3f(cofactor00, cofactor10, cofactor20,
										 cofactor01, cofactor11, cofactor21,
										 cofactor02, cofactor12, cofactor22);
	}
}

void Matrix3f::transpose()
{
	float temp;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = i + 1; j < 3; ++j)
		{
			temp = (*this)(i, j);
			(*this)(i, j) = (*this)(j, i);
			(*this)(j, i) = temp;
		}
	}
}

Matrix3f Matrix3f::transposed() const
{
	return Matrix3f
	(
		(*this)(0, 0), (*this)(1, 0), (*this)(2, 0),
		(*this)(0, 1), (*this)(1, 1), (*this)(2, 1),
		(*this)(0, 2), (*this)(1, 2), (*this)(2, 2)
	);
}

float Matrix3f::determinant3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	return
		(m00 * (m11 * m22 - m12 * m21)
		 - m01 * (m10 * m22 - m12 * m20)
		 + m02 * (m10 * m21 - m11 * m20));
}

Matrix3f Matrix3f::ones()
{
	return Matrix3f(1.f);
}

Matrix3f Matrix3f::identity()
{
	Matrix3f m;
	for (int i = 0; i < 3; ++i)
	{
		m.m_elements[i * 3 + i] = 1;
	}
	return m;
}

Matrix3f Matrix3f::rotateX(float radians)
{
	float c = cos(radians);
	float s = sin(radians);

	return Matrix3f
	(
		1, 0, 0,
		0, c, -s,
		0, s, c
	);
}

Matrix3f Matrix3f::rotateY(float radians)
{
	float c = cos(radians);
	float s = sin(radians);

	return Matrix3f
	(
		c, 0, s,
		0, 1, 0,
		-s, 0, c
	);
}

Matrix3f Matrix3f::rotateZ(float radians)
{
	float c = cos(radians);
	float s = sin(radians);

	return Matrix3f
	(
		c, -s, 0,
		s, c, 0,
		0, 0, 1
	);
}

Matrix3f Matrix3f::scaling(float sX, float sY, float sZ)
{
	return Matrix3f(
		sX, 0, 0,
		0, sY, 0,
		0, 0, sZ
	);
}

Matrix3f Matrix3f::uniformScaling(float s)
{
	return Matrix3f(
		s, 0, 0,
		0, s, 0,
		0, 0, s
	);
}

Matrix3f Matrix3f::rotation(const Vector3f& direction, float radians)
{
	Vector3f nDirection(direction.normalized());

	float cosA = cos(radians);
	float sinA = sin(radians);

	float x = nDirection.x();
	float y = nDirection.y();
	float z = nDirection.z();

	return Matrix3f
	(
		x * x * (1.0f - cosA) + cosA    , y * x * (1.0f - cosA) - z * sinA, z * x * (1.0f - cosA) + y * sinA,
		x * y * (1.0f - cosA) + z * sinA, y * y * (1.0f - cosA) + cosA    , z * y * (1.0f - cosA) - x * sinA,
		x * z * (1.0f - cosA) - y * sinA, y * z * (1.0f - cosA) + x * sinA, z * z * (1.0f - cosA) + cosA
	);
}

Matrix3f Matrix3f::rotation(const Quat4f q)
{
	Quat4f nQ = q.normalized();

	float xx = nQ.x() * nQ.x();
	float yy = nQ.y() * nQ.y();
	float zz = nQ.z() * nQ.z();
			  		
	float xy = nQ.x() * nQ.y();
	float zw = nQ.z() * nQ.w();
			 
	float xz = nQ.x() * nQ.z();
	float yw = nQ.y() * nQ.w();
			  
	float yz = nQ.y() * nQ.z();
	float xw = nQ.x() * nQ.w();

	return Matrix3f
	(
		1.0f - 2.0f * (yy + zz), 2.0f * (xy - zw), 2.0f * (xz + yw),
		2.0f * (xy + zw), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xw),
		2.0f * (xz - yw), 2.0f * (yz + xw), 1.0f - 2.0f * (xx + yy)
	);
}
#pragma endregion
/////////////////
// Operators Math
/////////////////
#pragma region Operators

// Scalar multiplication
Matrix3f operator * (const Matrix3f& m, float f)
{
	return Matrix3f(
		f*m(0, 0), f*m(0, 1), f*m(0, 2),
		f*m(1, 0), f*m(1, 1), f*m(1, 2),
		f*m(2, 0), f*m(2, 1), f*m(2, 2)
	);
}

Matrix3f operator * (float f, const Matrix3f& m)
{
	return Matrix3f(
		f*m(0, 0), f*m(0, 1), f*m(0, 2),
		f*m(1, 0), f*m(1, 1), f*m(1, 2),
		f*m(2, 0), f*m(2, 1), f*m(2, 2)
	);
}

// Matrix-Vector multiplication
Vector3f operator * (const Matrix3f& m, const Vector3f& v)
{
	Vector3f output(0, 0, 0);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			output[i] += m(i, j) * v[j];
		}
	}

	return output;
}

// Matrix-Matrix multiplication
Matrix3f operator * (const Matrix3f& m1, const Matrix3f& m2)
{
	Matrix3f product; // zeroes

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				product(i, k) += m1(i, j) * m2(j, k);
			}
		}
	}

	return product;
}
#pragma endregion