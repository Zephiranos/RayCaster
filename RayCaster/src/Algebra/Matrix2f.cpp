#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include "Vector2f.h"
#include "Matrix2f.h"

/////////////////////////////////
// 2x2 Matrix Math Implementation
//
// Nicolas Bordes - 10/2016
/////////////////////////////////

///////////////
// Constructors
///////////////
#pragma region Constructors

Matrix2f::Matrix2f(float fill)
{
	for (int i = 0; i < 4; ++i)
	{
		m_elements[i] = fill;
	}
}

Matrix2f::Matrix2f(float m00, float m01, float m10, float m11)
{
	m_elements[0] = m00;
	m_elements[1] = m01;
	m_elements[2] = m10;
	m_elements[3] = m11;
}

Matrix2f::Matrix2f(const Vector2f& v0, const Vector2f& v1, bool setColumns)
{
	if (setColumns)
	{
		setCol(0, v0);
		setCol(1, v1);
	}
	else
	{
		setRow(0, v0);
		setRow(1, v1);
	}
}

Matrix2f::Matrix2f(const Matrix2f& m)
{
	memcpy(m_elements, m.m_elements, 4 * sizeof(float));
}

Matrix2f& Matrix2f::operator = (const Matrix2f& m)
{
	if (this != &m)
	{
		memcpy(m_elements, m.m_elements, 4 * sizeof(float));
	}
	return *this;
}
#pragma endregion
//////////
// Utility
//////////
#pragma region Utility

const float& Matrix2f::operator () (int i, int j) const
{
	return m_elements[i * 2 + j];
}

float& Matrix2f::operator () (int i, int j)
{
	return m_elements[i * 2 + j];
}

Vector2f Matrix2f::getRow(int i) const
{
	return Vector2f(m_elements[i * 2], m_elements[i *2 + 1]);
}

void Matrix2f::setRow(int i, const Vector2f& v)
{
	m_elements[i * 2] = v.x();
	m_elements[i * 2 + 1] = v.y();
}

Vector2f Matrix2f::getCol(int i) const
{
	return Vector2f(m_elements[i], m_elements[i + 2]);
}

void Matrix2f::setCol(int i, const Vector2f& v)
{
	m_elements[i] = v.x();
	m_elements[i + 2] = v.y();
}

Matrix2f::operator float* ()
{
	return m_elements;
}

void Matrix2f::print()
{
	printf("[ %.4f %.4f ]\n[ %.4f %.4f ]\n",
		m_elements[0], m_elements[2],
		m_elements[1], m_elements[3]);
}
#pragma endregion
///////
// Math
///////
#pragma region Math

float Matrix2f::determinant()
{
	return Matrix2f::determinant2x2
	(
		m_elements[0], m_elements[1],
		m_elements[2], m_elements[3]
	);
}

Matrix2f Matrix2f::inverse(bool* pbIsSingular, float epsilon)
{
	float determinant(m_elements[0] * m_elements[3] - m_elements[2] * m_elements[1]);

	bool isSingular(fabs(determinant) < epsilon);
	if (isSingular)
	{
		if (pbIsSingular != NULL)
		{
			*pbIsSingular = true;
		}
		return Matrix2f();
	}
	else
	{
		if (pbIsSingular != NULL)
		{
			*pbIsSingular = false;
		}

		float recDeterminant = 1.0 / determinant;
		return recDeterminant * Matrix2f(m_elements[3], -m_elements[1], -m_elements[2], m_elements[0]);
	}
}

void Matrix2f::transpose()
{
	float m01(m_elements[1]);
	float m10(m_elements[2]);

	m_elements[1] = m10;
	m_elements[2] = m01;
}

Matrix2f Matrix2f::transposed() const
{
	return Matrix2f
	(
		(*this)(0, 0), (*this)(1, 0),
		(*this)(0, 1), (*this)(1, 1)
	);
}

float Matrix2f::determinant2x2(float m00, float m01, float m10, float m11)
{
	return m00 * m11 - m10 * m01;
}

Matrix2f Matrix2f::ones()
{
	return Matrix2f(1);
}

Matrix2f Matrix2f::identity()
{
	return Matrix2f(1, 0, 0, 1);
}

Matrix2f Matrix2f::rotation(float degree)
{
	float c = cos(degree);
	float s = sin(degree);

	return Matrix2f
	(
		c, -s,
		s, c
	);
}
#pragma endregion
/////////////////
// Operators Math
/////////////////
#pragma region Operators

// Scalar multiplication
Matrix2f operator * (const Matrix2f& m, float f)
{
	return Matrix2f(f*m(0, 0), f*m(0, 1), f*m(1, 0), f*m(1, 1));
}

Matrix2f operator * (float f, const Matrix2f& m)
{
	return Matrix2f(f*m(0, 0), f*m(0, 1), f*m(1, 0), f*m(1, 1));
}

// Matrix-Vector multiplication
Vector2f operator * (const Matrix2f& m, const Vector2f& v)
{
	return Vector2f(m(0, 0) * v.x() + m(0, 1) * v.y(),
					m(1, 0) * v.x() + m(1, 1) * v.y());
}

// Matrix-Matrix multiplication
Matrix2f operator * (const Matrix2f& m1, const Matrix2f& m2)
{
	Matrix2f product; // zeroes

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				product(i, k) += m1(i, j) * m2(j, k);
			}
		}
	}
	return product;
}
#pragma endregion
