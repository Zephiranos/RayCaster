#pragma once
#ifndef QUAT4F_H
#define QUAT4F_H

#include "Matrix3f.h"

class Vector3f;
class Vector4f;

///////////////////////////
// Quaternion Math Header
//
// Nicolas Bordes - 10/2016
///////////////////////////

class Quat4f
{
public:

	static const Quat4f ZERO;
	static const Quat4f IDENTITY;

	// Constructors
	Quat4f();
	Quat4f(float w, float x, float y, float z);
	Quat4f(const Quat4f& q);
	Quat4f& operator = (const Quat4f& q);
	Quat4f(const Vector3f& v);
	Quat4f(const Vector4f& v);

	// Utility
	const float& operator [] (int i) const;
	float& operator [] (int i);
	float w() const;
	float x() const;
	float y() const;
	float z() const;
	Vector3f xyz() const;
	Vector4f wxyz() const;

	void print();

	// Math
	float abs() const;
	float absSquared() const;
	void normalize();
	Quat4f normalized() const;

	void conjugate();
	Quat4f conjugated() const;

	void invert();
	Quat4f inverse() const;

	Quat4f log() const;
	Quat4f exp() const;

	Vector3f getAxisAngle(float* radiansOut);
	void setAxisAngle(float radians, const Vector3f& axis);

	static float dot(const Quat4f& q0, const Quat4f& q1);
	static Quat4f lerp(const Quat4f& q0, const Quat4f& q1, float alpha);
	static Quat4f slerp(const Quat4f& a, const Quat4f& b, float t, bool allowFlip = true);
	static Quat4f squad(const Quat4f& a, const Quat4f& tanA, const Quat4f& tanB, const Quat4f& b, float t);
	static Quat4f cubicInterpolate(const Quat4f& q0, const Quat4f& q1, const Quat4f& q2, const Quat4f& q3, float t);
	static Quat4f logDifference(const Quat4f& a, const Quat4f& b);
	static Quat4f squadTangent(const Quat4f& before, const Quat4f& center, const Quat4f& after);
	static Quat4f fromRotationMatrix(const Matrix3f& m);
	static Quat4f fromRotatedBasis(const Vector3f& x, const Vector3f& y, const Vector3f& z);

private:

	float m_elements[4];
};

Quat4f operator + (const Quat4f& q0, const Quat4f& q1);
Quat4f operator - (const Quat4f& q0, const Quat4f& q1);
Quat4f operator * (const Quat4f& q0, const Quat4f& q1);
Quat4f operator * (float f, const Quat4f& q);
Quat4f operator * (const Quat4f& q, float f);

#endif // QUAT4F_H