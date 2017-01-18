#pragma once
#ifndef RAY_H
#define RAY_H

#include <cassert>
#include <ostream>
#include <Vector3f.h>

///////////////////////////
// Ray class Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Ray
{
public:

	Ray(const Vector3f& orig, const Vector3f& dir);
	Ray(const Ray& r);

	const Vector3f& getOrigin() const;
	const Vector3f& getDirection() const;

	Vector3f pointAtParameter(float t) const;

private:

	// don't use this constructor
	Ray();

	Vector3f m_origin;
	Vector3f m_direction;

};

inline std::ostream& operator << (std::ostream& os, const Ray& r)
{
	os << "Ray <" << r.getOrigin() << ", " << r.getDirection() << ">";
	return os;
}

#endif // RAY_H
