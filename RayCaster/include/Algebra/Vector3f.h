#pragma once
#ifndef VECTOR_3F_H
#define VECTOR_3F_H

class Vector2f;

///////////////////////////
// 3D Vector Math Header
//
// Nicolas Bordes - 10/2016
///////////////////////////

class Vector3f
{
public:

	static const Vector3f ZERO;		// (0,0,0)
	static const Vector3f UP;		// (0,1,0)
	static const Vector3f RIGHT;	// (1,0,0)
	static const Vector3f FORWARD;	// (0,0,1)

	//Constructors
	Vector3f(float f = 0.f);
	Vector3f(float x, float y, float z);

	Vector3f(const Vector2f & xy, float z);
	Vector3f(float x, const Vector2f & yz);
	Vector3f(const Vector3f & vec);
	Vector3f & operator = (const Vector3f & vec);

	const float& operator [] (int i) const;
	float& operator [] (int i);

	float x() const;
	float y() const;
	float z() const;

	Vector2f xy() const;
	Vector2f yz() const;
	Vector2f xz() const;

	Vector3f xyz() const;
	Vector3f yzx() const;
	Vector3f zxy() const;

	operator const float*() const;	//type conversion
	operator float* ();				//type conversion
	void print() const;

	//Vector Math
	Vector3f& operator += (const Vector3f& v);
	Vector3f& operator -= (const Vector3f& v);
	Vector3f& operator *= (float f);

	float abs() const;
	float absSquared() const;
	void normalise();
	Vector3f normalized() const;
	Vector2f homogenized() const;

	void negate();

	static float dot(const Vector3f& v0, const Vector3f& v1);
	static Vector3f cross(const Vector3f& v0, const Vector3f& v1);
	static Vector3f lerp(const Vector3f& v0, const Vector3f& v1, float alpha); //v0*(1-alpha) + v1*alpha

	static Vector3f cubicInterpolate(const Vector3f& p0, const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, float t);

private:
	float m_elements[3];
};

/////////////////
// Operators Math
/////////////////

// between vectors
Vector3f operator + (const Vector3f& v0, const Vector3f& v1);
Vector3f operator - (const Vector3f& v0, const Vector3f& v1);
Vector3f operator * (const Vector3f& v0, const Vector3f& v1);
Vector3f operator / (const Vector3f& v0, const Vector3f& v1);

// negation
Vector3f operator - (const Vector3f& v);

// with scalar
Vector3f operator * (float f, const Vector3f& v);
Vector3f operator * (const Vector3f& v, float f);
Vector3f operator / (const Vector3f& v, float f);

bool operator == (const Vector3f& v0, const Vector3f& v1);
bool operator != (const Vector3f& v0, const Vector3f& v1);

#endif // VECTOR_2F_H