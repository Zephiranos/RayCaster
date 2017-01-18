#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "Vector4f.h"
#include "Vector3f.h"
#include "Vector2f.h"

////////////////////////////////
// 4D Vector Math Implementation
////////////////////////////////

///////////////
// Constructors
///////////////
#pragma region Constructors

Vector4f::Vector4f(float f)
{
	m_elements[0] = f;
	m_elements[1] = f;
	m_elements[2] = f;
	m_elements[3] = f;
}

Vector4f::Vector4f(float x, float y, float z, float w)
{
	m_elements[0] = x;
	m_elements[1] = y;
	m_elements[2] = z;
	m_elements[3] = w;
}

Vector4f::Vector4f(float buffer[4])
{
	m_elements[0] = buffer[0];
	m_elements[1] = buffer[1];
	m_elements[2] = buffer[2];
	m_elements[3] = buffer[3];
}

Vector4f::Vector4f(const Vector2f & xy, float z, float w)
{
	m_elements[0] = xy.x();
	m_elements[1] = xy.y();
	m_elements[2] = z;
	m_elements[3] = w;
}

Vector4f::Vector4f(float x, const Vector2f & yz, float w)
{
	m_elements[0] = x;
	m_elements[1] = yz.x();
	m_elements[2] = yz.y();
	m_elements[3] = w;
}

Vector4f::Vector4f(float x, float y, const Vector2f & zw)
{
	m_elements[0] = x;
	m_elements[1] = y;
	m_elements[2] = zw.x();
	m_elements[3] = zw.y();
}

Vector4f::Vector4f(const Vector3f & xyz, float w)
{
	m_elements[0] = xyz.x();
	m_elements[1] = xyz.y();
	m_elements[2] = xyz.z();
	m_elements[3] = w;
}

Vector4f::Vector4f(float x, const Vector3f & yzw)
{
	m_elements[0] = x;
	m_elements[1] = yzw.x();
	m_elements[2] = yzw.y();
	m_elements[3] = yzw.z();
}

Vector4f::Vector4f(const Vector4f & vec)
{
	m_elements[0] = vec.x();
	m_elements[1] = vec.y();
	m_elements[2] = vec.z();
	m_elements[3] = vec.w();
}

Vector4f & Vector4f::operator = (const Vector4f & vec)
{
	if (this != &vec)
	{
		m_elements[0] = vec.x();
		m_elements[1] = vec.y();
		m_elements[2] = vec.z();
		m_elements[3] = vec.w();
	}
	return *this;
}
#pragma endregion
//////////
// Utility
//////////
#pragma region Utility

const float& Vector4f::operator [] (int i) const
{
	return m_elements[i];
}

float& Vector4f::operator [] (int i)
{
	return m_elements[i];
}

float Vector4f::x() const
{
	return m_elements[0];
}

float Vector4f::y() const
{
	return m_elements[1];
}

float Vector4f::z() const
{
	return m_elements[2];
}

float Vector4f::w() const
{
	return m_elements[3];
}

Vector2f Vector4f::xy() const
{
	return Vector2f(m_elements[0], m_elements[1]);
}
Vector2f Vector4f::yz() const
{
	return Vector2f(m_elements[0], m_elements[1]);
}
Vector2f Vector4f::zw() const
{
	return Vector2f(m_elements[0], m_elements[1]);
}
Vector2f Vector4f::wx() const
{
	return Vector2f(m_elements[0], m_elements[1]);
}

Vector3f Vector4f::xyz() const
{
	return Vector3f(m_elements[0], m_elements[1], m_elements[2]);
}

Vector3f Vector4f::yzw() const
{
	return Vector3f(m_elements[1], m_elements[2], m_elements[3]);
}

Vector3f Vector4f::zwx() const
{
	return Vector3f(m_elements[2], m_elements[3], m_elements[1]);
}

Vector3f Vector4f::wxy() const
{
	return Vector3f(m_elements[3], m_elements[0], m_elements[1]);
}

Vector4f::operator const float* () const
{
	return m_elements;
}

Vector4f::operator float* ()
{
	return m_elements;
}

void Vector4f::print() const
{
	printf("< %.4f, %.4f , %.4f, %.4f >\n", m_elements[0], m_elements[1], m_elements[2], m_elements[3]);
}
#pragma endregion
///////
// Math
///////
#pragma region Math

float Vector4f::abs() const
{
	return sqrt(absSquared());
}

float Vector4f::absSquared() const
{
	return m_elements[0] * m_elements[0] + m_elements[1] * m_elements[1] + m_elements[2] * m_elements[2] + m_elements[3] * m_elements[3];
}

void Vector4f::normalise()
{
	float norm = abs();
	m_elements[0] /= norm;
	m_elements[1] /= norm;
	m_elements[2] /= norm;
	m_elements[3] /= norm;
}

Vector4f Vector4f::normalized() const
{
	float norm = abs();
	return Vector4f(m_elements[0] / norm, m_elements[1] / norm, m_elements[2] / norm, m_elements[3] / norm);
}

void Vector4f::negate()
{
	m_elements[0] = -m_elements[0];
	m_elements[1] = -m_elements[1];
	m_elements[2] = -m_elements[2];
	m_elements[3] = -m_elements[3];
}

Vector3f Vector4f::homogenized() const
{
	return Vector3f(m_elements[0] / m_elements[3], m_elements[1] / m_elements[3], m_elements[2] / m_elements[3]);
}

Vector4f& Vector4f::operator += (const Vector4f& vec)
{
	m_elements[0] += vec[0];
	m_elements[1] += vec[1];
	m_elements[2] += vec[2];
	m_elements[3] += vec[3];
	return *this;
}

Vector4f& Vector4f::operator -= (const Vector4f& vec)
{
	m_elements[0] -= vec[0];
	m_elements[1] -= vec[1];
	m_elements[2] -= vec[2];
	m_elements[3] -= vec[3];
	return *this;
}

Vector4f& Vector4f::operator *= (float f)
{
	m_elements[0] *= f;
	m_elements[1] *= f;
	m_elements[2] *= f;
	m_elements[3] *= f;
	return *this;
}

/////////
// Static
/////////
float Vector4f::dot(const Vector4f& v0, const Vector4f& v1)
{
	return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
}

Vector4f Vector4f::lerp(const Vector4f& v0, const Vector4f& v1, float alpha)
{
	return alpha * (v1 - v0) + v0;
}
#pragma endregion
////////////
// Operators
////////////
#pragma region Operators

Vector4f operator + (const Vector4f& v0, const Vector4f& v1)
{
	return Vector4f(v0.x() + v1.x(), v0.y() + v1.y(), v0.z() + v1.z(), v0.w() + v1.w());
}

Vector4f operator - (const Vector4f& v0, const Vector4f& v1)
{
	return Vector4f(v0.x() - v1.x(), v0.y() - v1.y(), v0.z() - v1.z(), v0.w() - v1.w());
}

Vector4f operator * (const Vector4f& v0, const Vector4f& v1)
{
	return Vector4f(v0.x() * v1.x(), v0.y() * v1.y(), v0.z() * v1.z(), v0.w() * v1.w());
}

Vector4f operator / (const Vector4f& v0, const Vector4f& v1)
{
	return Vector4f(v0.x() / v1.x(), v0.y() / v1.y(), v0.z() / v1.z(), v0.w() / v1.w());
}

Vector4f operator - (const Vector4f& v)
{
	return Vector4f(-v.x(), -v.y(), -v.z(), -v.w());
}

Vector4f operator * (float f, const Vector4f& v)
{
	return Vector4f(f * v.x(), f * v.y(), f * v.z(), f * v.w());
}

Vector4f operator * (const Vector4f& v, float f)
{
	return Vector4f(v.x() * f, v.y() * f, v.z() * f, v.w() * f);
}

Vector4f operator / (const Vector4f& v, float f)
{
	return Vector4f(v.x() / f, v.y() / f, v.z() / f, v.w() / f);
}

bool operator == (const Vector4f& v0, const Vector4f& v1)
{
	return ((v0.x() == v1.x() && v0.y() == v1.y() && v0.z() == v1.z() && v0.w() == v1.w()));
}

bool operator != (const Vector4f& v0, const Vector4f& v1)
{
	return ((v0.x() != v1.x() || v0.y() != v1.y() || v0.z() != v1.z() || v0.w() != v1.w()));
}
#pragma endregion