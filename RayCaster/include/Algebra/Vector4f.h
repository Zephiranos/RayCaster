#pragma once
#ifndef VECTOR_4F_H
#define VECTOR_4F_H

class Vector2f;
class Vector3f;

///////////////////////////
// 4D Vector Math Header
//
// Nicolas Bordes - 10/2016
///////////////////////////

class Vector4f
{
public:

	//Constructors
	Vector4f(float f = 0.f);
	Vector4f(float x, float y, float z, float w);
	Vector4f(float buffer[4]);
		  
	Vector4f(const Vector2f & xy, float z, float w);
	Vector4f(float x, const Vector2f & yz, float w);
	Vector4f(float x, float y, const Vector2f & zw);

	Vector4f(const Vector3f & xyz, float w);
	Vector4f(float x, const Vector3f & yzw );

	Vector4f(const Vector4f & vec);
	Vector4f & operator = (const Vector4f & vec);

	const float& operator [] (int i) const;
	float& operator [] (int i);

	float x() const;
	float y() const;
	float z() const;
	float w() const;

	Vector2f xy() const;
	Vector2f yz() const;
	Vector2f zw() const;
	Vector2f wx() const;

	Vector3f xyz() const;
	Vector3f yzw() const;
	Vector3f zwx() const;
	Vector3f wxy() const;

	operator const float*() const;	//type conversion
	operator float* ();				//type conversion
	void print() const;

	//Vector Math
	Vector4f& operator += (const Vector4f& v);
	Vector4f& operator -= (const Vector4f& v);
	Vector4f& operator *= (float f);

	void homogenize();
	Vector3f homogenized() const;

	float abs() const;
	float absSquared() const;
	void normalise();
	Vector4f normalized() const;

	void negate();

	static float dot(const Vector4f& v0, const Vector4f& v1);
	static Vector4f lerp(const Vector4f& v0, const Vector4f& v1, float alpha); //v0*(1-alpha) + v1*alpha

private:
	float m_elements[4];
};

/////////////////
// Operators Math
/////////////////

// between vectors
Vector4f operator + (const Vector4f& v0, const Vector4f& v1);
Vector4f operator - (const Vector4f& v0, const Vector4f& v1);
Vector4f operator * (const Vector4f& v0, const Vector4f& v1);
Vector4f operator / (const Vector4f& v0, const Vector4f& v1);

// negation
Vector4f operator - (const Vector4f& v);

// with scalar
Vector4f operator * (float f, const Vector4f& v);
Vector4f operator * (const Vector4f& v, float f);
Vector4f operator / (const Vector4f& v, float f);

bool operator == (const Vector4f& v0, const Vector4f& v1);
bool operator != (const Vector4f& v0, const Vector4f& v1);

#endif // VECTOR_4F_H