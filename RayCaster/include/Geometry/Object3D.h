#pragma once
#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Ray.h"
#include "Hit.h"
#include "Material.h"

/////////////////////////////////
// Object3D Abstract class Header
//
// Nicolas Bordes - 10/2016
/////////////////////////////////
class Object3D
{
public:
	Object3D()
	{
		m_material = NULL;
	}
	virtual ~Object3D() {}

	Object3D(Material* material) {
		m_material = material;
	}

	virtual bool intersect(const Ray& r, Hit& h, float tmin) = 0;

	char* type;
protected:

	Material* m_material;
};

#endif

