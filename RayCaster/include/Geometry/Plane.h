#pragma once
#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include "Vector3f.h"
#include <cmath>

///////////////////////////
// Plane Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Plane : public Object3D
{
public:
	// Constructors
	Plane();
	Plane(const Vector3f& normal, float d, Material* m);
	//Destructors
	~Plane();
	virtual bool intersect(const Ray& r, Hit& h, float tmin);
	Vector3f getNormal() const;
	float getOffset() const;

protected:
	Vector3f m_normal;
	float m_D;
};
#endif //PLANE_H


