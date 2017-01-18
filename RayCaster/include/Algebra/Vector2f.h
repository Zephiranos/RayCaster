#pragma once
#ifndef VECTOR_2F_H
#define VECTOR_2F_H

///////////////////////////
// 2D Vector Math Header
//
// Nicolas Bordes - 10/2016
///////////////////////////

class Vector2f
{
public:

	static const Vector2f ZERO; // (0.0)
	static const Vector2f UP;   // (0,1)
	static const Vector2f RIGHT;// (1,0)

	//Constructors
	Vector2f(float f = 0.f);
	Vector2f(float x, float y);

	Vector2f(const Vector2f & vec);
	Vector2f & operator= (const Vector2f & vec);

	const float& operator [] (int i) const;
	float& operator [] (int i);

	float x() const;
	float y() const;

	Vector2f xy() const;
	Vector2f yx() const;
	Vector2f xx() const;
	Vector2f yy() const;

	operator const float*() const; //type conversion
	operator float* (); //type conversion
	void print() const;

	//Vector Math
	Vector2f& operator += (const Vector2f& v);
	Vector2f& operator -= (const Vector2f& v);
	Vector2f& operator *= (float f);

	Vector2f normal() const;
	float abs() const;
	float absSquared() const;
	void normalise();
	Vector2f normalized() const;

	void negate();

	static float dot(const Vector2f& v0, const Vector2f& v1);
	static Vector2f lerp(const Vector2f& v0, const Vector2f& v1, float alpha); //v0*(1-alpha) + v1*alpha

private:
	float m_elements[2];
};

/////////////////
// Operators Math
/////////////////

// between vectors
Vector2f operator + (const Vector2f& v0, const Vector2f& v1);
Vector2f operator - (const Vector2f& v0, const Vector2f& v1);
Vector2f operator * (const Vector2f& v0, const Vector2f& v1);
Vector2f operator / (const Vector2f& v0, const Vector2f& v1);

// negation
Vector2f operator - (const Vector2f& v);

// with scalar
Vector2f operator * (float f, const Vector2f& v);
Vector2f operator * (const Vector2f& v, float f);
Vector2f operator / (const Vector2f& v, float f);

bool operator == (const Vector2f& v0, const Vector2f& v1);
bool operator != (const Vector2f& v0, const Vector2f& v1);

#endif // VECTOR_2F_H