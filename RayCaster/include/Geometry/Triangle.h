#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include "Vector3f.h"
#include "Matrix3f.h"

///////////////////////////
// Triangle Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Triangle : public Object3D
{
public:
	Triangle();
	///@param a b c are three vertex positions of the triangle
	Triangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m);

	virtual bool intersect(const Ray& ray, Hit& hit, float tmin);
	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:
	Vector3f m_a;
	Vector3f m_b;
	Vector3f m_c;
};

#endif //TRIANGLE_H
