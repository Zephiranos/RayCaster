#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "Vector2f.h"
#include "Vector3f.h"

////////////////////////////////
// 2D Vector Math Implementation
////////////////////////////////

/////////
// Static
/////////
const Vector2f Vector2f::ZERO = Vector2f(0, 0);
const Vector2f Vector2f::UP = Vector2f(0, 1);
const Vector2f Vector2f::RIGHT = Vector2f(1, 0);
///////////////
// Constructors
///////////////
#pragma region Constructors

Vector2f::Vector2f(float f)
{
	m_elements[0] = f;
	m_elements[1] = f;
}

Vector2f::Vector2f(float x, float y)
{
	m_elements[0] = x;
	m_elements[1] = y;
}

Vector2f::Vector2f(const Vector2f& vec)
{
	m_elements[0] = vec[0];
	m_elements[1] = vec[1];
}

Vector2f& Vector2f::operator = (const Vector2f& vec)
{
	if (this != &vec)
	{
		m_elements[0] = vec[0];
		m_elements[1] = vec[1];
	}
	return *this;
}
#pragma endregion
//////////
// Utility
//////////
#pragma region Utility

const float& Vector2f::operator [] (int i) const
{
	return m_elements[i];
}

float& Vector2f::operator [] (int i)
{
	return m_elements[i];
}

float Vector2f::x() const
{
	return m_elements[0];
}

float Vector2f::y() const
{
	return m_elements[1];
}

Vector2f Vector2f::xy() const
{
	return *this;
}

Vector2f Vector2f::yx() const
{
	return Vector2f(m_elements[0], m_elements[1]);
}

Vector2f Vector2f::xx() const
{
	return Vector2f(m_elements[0], m_elements[1]);
}

Vector2f Vector2f::yy() const
{
	return Vector2f(m_elements[0], m_elements[1]);
}

Vector2f::operator const float* () const
{
	return m_elements;
}

Vector2f::operator float* ()
{
	return m_elements;
}

void Vector2f::print() const
{
	printf("< %.4f, %.4f >\n", m_elements[0], m_elements[1]);
}
#pragma endregion
///////
// Math
///////
#pragma region Math

Vector2f Vector2f::normal() const
{
	return Vector2f(-m_elements[1], m_elements[0]);
}

float Vector2f::abs() const
{
	return sqrt(absSquared());
}

float Vector2f::absSquared() const
{
	return m_elements[0] * m_elements[0] + m_elements[1] * m_elements[1];
}

void Vector2f::normalise()
{
	float norm = abs();
	m_elements[0] /= norm;
	m_elements[1] /= norm;
}

Vector2f Vector2f::normalized() const
{
	float norm = abs();
	return Vector2f(m_elements[0] / norm, m_elements[1] / norm);
}

void Vector2f::negate()
{
	m_elements[0] = -m_elements[0];
	m_elements[1] = -m_elements[1];
}

Vector2f& Vector2f::operator += (const Vector2f& vec)
{
	m_elements[0] += vec[0];
	m_elements[1] += vec[1];
	return *this;
}

Vector2f& Vector2f::operator -= (const Vector2f& vec)
{
	m_elements[0] -= vec[0];
	m_elements[1] -= vec[1];
	return *this;
}

Vector2f& Vector2f::operator *= (float f)
{
	m_elements[0] *= f;
	m_elements[1] *= f;
	return *this;
}

float Vector2f::dot(const Vector2f& v0, const Vector2f& v1)
{
	return v0[0] * v1[0] + v0[1] * v1[1];
}

Vector2f Vector2f::lerp(const Vector2f& v0, const Vector2f& v1, float alpha)
{
	return alpha * (v1 - v0) + v0;
}
#pragma endregion
////////////
// Operators
////////////
#pragma region Operators

Vector2f operator + (const Vector2f& v0, const Vector2f& v1)
{
	return Vector2f(v0.x() + v1.x(), v0.y() + v1.y());
}

Vector2f operator - (const Vector2f& v0, const Vector2f& v1)
{
	return Vector2f(v0.x() - v1.x(), v0.y() - v1.y());
}

Vector2f operator * (const Vector2f& v0, const Vector2f& v1)
{
	return Vector2f(v0.x() * v1.x(), v0.y() * v1.y());
}

Vector2f operator / (const Vector2f& v0, const Vector2f& v1)
{
	return Vector2f(v0.x() / v1.x(), v0.y() / v1.y());
}

Vector2f operator - (const Vector2f& v)
{
	return Vector2f(-v.x(), -v.y());
}

Vector2f operator * (float f, const Vector2f& v)
{
	return Vector2f(f * v.x(), f * v.y());
}

Vector2f operator * (const Vector2f& v, float f)
{
	return Vector2f(v.x() * f, v.y() * f);
}

Vector2f operator / (const Vector2f& v, float f)
{
	return Vector2f(v.x() / f, v.y() / f);
}

bool operator == (const Vector2f& v0, const Vector2f& v1)
{
	return ((v0.x() == v1.x() && v0.y() == v1.y()));
}

bool operator != (const Vector2f& v0, const Vector2f& v1)
{
	return ((v0.x() != v1.x() || v0.y() != v1.y()));
}
#pragma endregion