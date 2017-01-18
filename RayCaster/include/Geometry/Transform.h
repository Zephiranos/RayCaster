#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix4f.h"
#include "Object3D.h"
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
///////////////////////////
// Transform Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Transform : public Object3D
{
public:
	Transform();
	Transform(const Matrix4f& m, Object3D* obj);

	~Transform();

	virtual bool intersect(const Ray& r, Hit& h, float tmin);
	Object3D * getObject() const;
	Matrix4f getTransformationMatrix() const;

protected:
	Object3D* m_obj; //un-transformed object	
	Matrix4f m_transMatrix;
};

#endif //TRANSFORM_H
