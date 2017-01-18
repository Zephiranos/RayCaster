#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include "Vector3f.h"
#include <cmath>

#include <iostream>

///////////////////////////
// Sphere class Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Sphere : public Object3D
{
public:
	// Constructors
	Sphere();
	Sphere(Vector3f center, float radius, Material* material);
	//Destructors
	~Sphere();

	virtual bool intersect(const Ray& r, Hit& h, float tmin);
	Vector3f getCenter() const;
	float getRadius() const;

protected:
	Vector3f m_center;
	float m_radius;
};


#endif
