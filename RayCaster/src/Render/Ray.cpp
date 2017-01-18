#include "Ray.h"

///////////////////////////
// Ray class Implementation
//
// Nicolas Bordes - 10/2016
///////////////////////////

///////////////
// Constructors
///////////////
#pragma region Constructors

Ray::Ray(const Vector3f& orig, const Vector3f& dir)
{
	m_origin = orig;
	m_direction = dir;
}

Ray::Ray(const Ray& r)
{
	m_origin = r.m_origin;
	m_direction = r.m_direction;
}
#pragma endregion
//////////
// Utility
//////////
#pragma region Utility

const Vector3f& Ray::getOrigin() const
{
	return m_origin;
}

const Vector3f& Ray::getDirection() const
{
	return m_direction;
}

Vector3f Ray::pointAtParameter(float t) const
{
	return m_origin + m_direction * t;
}
#pragma endregion